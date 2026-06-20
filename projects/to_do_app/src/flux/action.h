#pragma once
#include <QString>
#include "../tasks/FilterType.h"

struct AddTaskPayload
{
    QString text;
};
 
struct ToggleCompletePayload
{
    QString taskId;
};
 
struct DeleteTaskPayload
{
    QString taskId;
};
 
struct SetFilterPayload
{
    FilterType::Type filter;
};

using ActionPayload = std::variant<AddTaskPayload,
                                    ToggleCompletePayload,
                                    DeleteTaskPayload,
                                    SetFilterPayload>;

enum class ActionType
{
    AddTask,
    ToggleComplete,
    DeleteTask,
    SetFilter
};

struct Action
{
    ActionType type;
    ActionPayload payload;
};