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
#include <QDate>

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

    if (rows.isEmpty()) return itemData;

    // store data types
    QList<DataType> columnTypes{};
    QVariantMap sampleRow = rows.at(0).toMap();
    for (int i = 0; i < sampleRow.size(); i++) {
        DataType type = detectCellType(sampleRow.value(itemData.headers().at(i)).toString());
        columnTypes.append(type);
    }
    itemData.setDataType(columnTypes);

    return itemData;
}

DataType FileParser::detectCellType(const QString &cellStr)
{
    QString str = cellStr.trimmed();
    if (str.isEmpty()) return DataType::STRING;

    // check for int
    bool isInt;
    str.toInt(&isInt);
    if (isInt) return DataType::INTERGER;

    // check for double
    bool isDouble;
    str.toDouble(&isDouble);
    if (isDouble) return DataType::DOUBLE;

    // date time
    QDate date = QDate::fromString(str, Qt::ISODate);
    if (date.isValid()) return DataType::DATE;

    return DataType::STRING;
}