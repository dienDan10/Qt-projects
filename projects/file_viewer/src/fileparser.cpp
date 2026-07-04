/**
 * @file      fileparser.cpp
 * @author    diendanx
 * @date      2026-6-29
 *
 * Copyright (c) 2026 diendanx.
 * All rights reserved.
 */
#include "fileparser.h"
#include <QFile>
#include <QTextStream>
#include <QVariantList>
#include <QVariantMap>
#include <QDebug>

FileParser::FileParser() {}

// for now, read the file in the main thread
ItemData FileParser::parseFile(QString &filePath)
{
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw QString("Cannot open file!");
    }

    QTextStream in(&file);
    ItemData itemData{};
    // read the header
    if (!in.atEnd()) {
        QStringList headers = in.readLine().split(',');
        itemData.setHeaders(headers);
    }

    // read the rows
    QVariantList rows;
    while (!in.atEnd()) {
        QStringList cols = in.readLine().split(',');
        QVariantMap row;
        for (int i = 0; i < cols.length(); i++) {
            row.insert(itemData.headers().at(i), cols.at(i));
        }
        rows.append(row);
    }
    itemData.setRows(rows);

    return itemData;
}