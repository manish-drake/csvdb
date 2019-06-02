#ifndef CSVLIST_H
#define CSVLIST_H
#include <vector>
#include <string>
#include <iterator>

const char DL[] = ",";
const int MAX_ROW_SZ = 255;
class CSVList
{
    using row = std::vector<std::string>;
    struct csv{
        row m_row;
        row *m_fields;
        std::string toString()
        {
            std::string strRow = "";
            for (const auto &col : m_row)             
            {
                strRow += col;
                strRow += ",";
            }
            strRow.pop_back();
            return strRow;
        }
        csv(const row &arg, row *fields):
            m_row{arg},
            m_fields{fields}
        {
            
        }

        int colIndex(const std::string &colName) const
        {
            int index = 0;
            for(auto &field:*m_fields)
            {
                if(field == colName) return index;
                index += 1;
            }
            return -1;
        }
        std::string &operator[](const int &index)
        {
            return m_row[index];
        }
        const std::string &operator[](const int &index) const
        {
            return m_row[index];
        }
        std::string *operator[](const std::string &fieldName)
        {
            int index = colIndex(fieldName);
            if(index >= 0)
                return &m_row[index];
            else
                return nullptr;            
        }
        const std::string *operator[](const std::string &fieldName) const
        {
            int index = colIndex(fieldName);
            if(index >= 0)
                return &m_row[index];
            else
                return nullptr;  
        }

    };
    using rows = std::vector<csv>;
    using const_row_iterator =  rows::const_iterator;

    void split(const char *str, const char *delimitter, row *collection);
    row m_fields;
    rows m_rows;
    std::string *get(const row::size_type &row, const row::size_type &col);
    std::string *get(const row::size_type &row, const std::string &fieldName);
    std::string toString()
    {        
        std::string strRow;
        for (const auto &col : m_fields) 
        {
            strRow += col;
            strRow += ",";
        }
        strRow.pop_back();
        return strRow;    
    }
public:
    CSVList();
    CSVList(const char *fields);
    void Add(const char *data);
    const_row_iterator begin() const
    {
        return m_rows.cbegin();
    }
    const_row_iterator end() const
    {
        return m_rows.cend();
    }
    void Save(const char *filename);
    void Open(const char *filename);

};

#endif // CSVLIST_H
