#include <fstream>
#include <string>
#include <exception>
#include <vector>

using namespace std;

template <typename T>
class Database
{
    const string File_Name;
    size_t DB_size;

public:
    Database(string File_Name) : File_Name(File_Name)
    {
        if (!File_Name.ends_with(".dat"))
        {
            throw runtime_error("File must have a .dat extension");
        }

        fstream file(File_Name, ios::binary | ios::app);
        file.seekg(0, ios::end);
        DB_size = file.tellp() / sizeof(T);
        file.close();
    }

    // ──────────────────────────────────────────────
    // Append a new entry at the end
    // ──────────────────────────────────────────────
    void insert(T entry)
    {
        fstream file(File_Name, ios::binary | ios::app | ios::ate);
        file.write((char *)&entry, sizeof(T));
        DB_size++;
        file.close();
    }

    // ──────────────────────────────────────────────
    // Insert a new entry at a specific index,
    // shifting everything after it to the right
    // ──────────────────────────────────────────────
    void insert_at(T entry, size_t index)
    {
        if (index > DB_size)
            throw out_of_range("Index out of range");

        // Read all entries into memory
        vector<T> buffer(DB_size);
        {
            fstream file(File_Name, ios::binary | ios::in);
            file.read((char *)buffer.data(), DB_size * sizeof(T));
        }

        // Insert the new entry at the desired position
        buffer.insert(buffer.begin() + index, entry);

        // Write everything back
        {
            fstream file(File_Name, ios::binary | ios::out | ios::trunc);
            file.write((char *)buffer.data(), buffer.size() * sizeof(T));
        }

        DB_size++;
    }

    // ──────────────────────────────────────────────
    // Read entry by index
    // ──────────────────────────────────────────────
    T operator[](size_t index)
    {
        if (index >= DB_size)
            throw out_of_range("Index out of range");

        T entry;
        fstream file(File_Name, ios::binary | ios::in);
        file.seekg(index * sizeof(T), ios::beg);
        file.read((char *)&entry, sizeof(T));
        file.close();
        return entry;
    }

    // ──────────────────────────────────────────────
    // Overwrite the entry at a specific index
    // ──────────────────────────────────────────────
    void update(T entry, size_t index)          // fixed: size_t not size
    {
        if (index >= DB_size)
            throw out_of_range("Index out of range");

        fstream file(File_Name, ios::binary | ios::in | ios::out); // fixed: need ios::in too
        file.seekp(index * sizeof(T), ios::beg);
        file.write((char *)&entry, sizeof(T));
        file.close();
    }

    // ──────────────────────────────────────────────
    // Remove the entry at a specific index,
    // shifting everything after it to the left
    // ──────────────────────────────────────────────
    void remove(size_t index)                   // fixed: 'delete' is a keyword
    {
        if (index >= DB_size)
            throw out_of_range("Index out of range");

        // Read all entries after the target into a buffer
        size_t entries_after = DB_size - index - 1;
        vector<T> buffer(entries_after);

        {
            fstream file(File_Name, ios::binary | ios::in);
            file.seekg((index + 1) * sizeof(T), ios::beg);
            file.read((char *)buffer.data(), entries_after * sizeof(T));
        }

        // Write them back one position earlier, then truncate
        {
            fstream file(File_Name, ios::binary | ios::in | ios::out);
            file.seekp(index * sizeof(T), ios::beg);
            file.write((char *)buffer.data(), entries_after * sizeof(T));
        }

        // Truncate the file to remove the now-dangling last record
        filesystem::resize_file(File_Name, (DB_size - 1) * sizeof(T));

        DB_size--;
    }

    // ──────────────────────────────────────────────
    // Helpers
    // ──────────────────────────────────────────────
    size_t size() const { return DB_size; }

    bool empty() const { return DB_size == 0; }
};