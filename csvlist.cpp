#include "csvlist.h"
#include <stdio.h>
#include <string.h>

CSVList::CSVList()
{

}

void CSVList::split(const char *str, const char *delimitter, row *collection)
{
    collection->clear();
    char workingCopy[MAX_ROW_SZ] = {0};
    strcpy(workingCopy, str);
    char *ptr = strtok(workingCopy, delimitter);
    while (ptr) {
        collection->push_back(ptr);
        ptr = strtok(nullptr, delimitter);
    }
}


std::string *CSVList::get(const row::size_type &row, const row::size_type &col)
{
    return &m_rows[row][col];
}

std::string *CSVList::get(const row::size_type &row, const std::string &fieldName)
{
    return m_rows[row][fieldName];
}

CSVList::CSVList(const char *fields)
{
    split(fields, DL, &m_fields);
}

void CSVList::Add(const char *data)
{
    m_rows.push_back(csv(row(), &m_fields));
    auto &newRow = m_rows[m_rows.size()-1].m_row;
    split(data, DL, &newRow);
}

void CSVList::Save(const char *filename)
{
    auto fp = fopen(filename, "w+");

    fprintf(fp, "%s\n", toString().c_str());
    for(auto &each: m_rows)
    {
        fprintf(fp, "%s\n", each.toString().c_str());
    }
    fclose(fp);
}
void CSVList::Open(const char *filename)
{
    m_fields.clear();
    m_rows.clear();
    auto fp = fopen(filename, "r");
    char rowBuff[MAX_ROW_SZ] = {0};
    if(fgets(rowBuff, MAX_ROW_SZ, (FILE*)fp))
    {
        rowBuff[strlen(rowBuff) - 1] = '\0';
        split(rowBuff, DL, &m_fields);
        while(fgets(rowBuff, MAX_ROW_SZ, (FILE*)fp))
        {
            rowBuff[strlen(rowBuff) - 1] = '\0';
            Add(rowBuff);
        }
    }    
    fclose(fp);
}