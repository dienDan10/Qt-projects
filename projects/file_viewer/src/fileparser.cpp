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
#include <QFileInfo>
#include <QTextStream>
#include <QVariantList>
#include <QVariantMap>
#include <QDate>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

FileParser::FileParser() {}

// for now, read the file in the main thread
ItemData FileParser::parseFile(const QString &filePath)
{
    QFileInfo info(filePath);
    QString extension = info.suffix().toLower();

    if (extension == QStringLiteral("csv")) {
        return parseCSVFIle(filePath);
    }

    if (extension == QStringLiteral("json")) {
        return parseJsonFile(filePath);
    }

    throw QString("Unsupported file format (%1)").arg(extension);
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

ItemData FileParser::parseCSVFIle(const QString &filePath)
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

    file.close();
    return itemData;
}

ItemData FileParser::parseJsonFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw QString("Cannot open file!");
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (error.error != QJsonParseError::NoError) {
        throw QString("JSON parse error. Check the json file format");
    }

    if (doc.isObject()) {
        throw QString("JSON file must contain an array of object.");
    }

    QJsonArray itemsArr = doc.array();
    if (itemsArr.isEmpty()) {
        return ItemData();
    }

    ItemData itemData;

    // get the headers
    QJsonObject item1 = itemsArr.at(0).toObject();
    QStringList header = item1.keys();
    itemData.setHeaders(header);

    // get the types
    QList<DataType> columnTypes{};
    for (int i = 0; i < header.length(); i++) {
        DataType type = detectCellType(item1[header.at(i)].toString());
        columnTypes.append(type);
    }
    itemData.setDataType(columnTypes);

    // get the row data
    QVariantList rows;
    QVariantMap map;
    for (int i = 0; i < itemsArr.size(); i++) {
        QJsonObject item = itemsArr.at(i).toObject();
        for (int j = 0; j < header.length(); j++) {
            map.insert(header.at(j), item[header.at(j)].toVariant());
        }
        rows.append(map);
        map.clear();
    }
    itemData.setRows(rows);

    return itemData;
}