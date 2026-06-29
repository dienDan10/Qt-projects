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
    static ItemData parseFile(QString& filePath);
};

#endif // FILEPARSER_H
