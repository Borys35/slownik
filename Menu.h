#pragma once

#include <string>
#include "BaseList.hpp"
#include "PriorityQueueBase.hpp"

void showMenu();
void showOperationMenu();
void showPriorityQueueMenu();
template<class T>
void performListOperations(BaseList<T>& list, const std::string& listName);
template<class T>
void performPriorityQueueOperations(PriorityQueueBase<T>& queue, const std::string& queueName);
void runMenu();