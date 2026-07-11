/**
 * @file      fileparser.h
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QString>
#include "itemdata.h"

class FileParser
{
public:
    FileParser();

public:
    static ItemData parseFile(const QString& filePath);

private:
    static DataType detectCellType(const QString& cellStr);
    static ItemData parseCSVFIle(const QString& filePath);
    static ItemData parseJsonFile(const QString& filePath);
};

#endif // FILEPARSER_H
