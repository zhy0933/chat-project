#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include "QStyle"

/**
 * @brief repolish用来根据属性刷新qss
 */
extern std::function<void(QWidget*)> repolish;

#endif // GLOBAL_H
