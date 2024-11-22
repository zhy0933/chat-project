#include "global.h"

std::function<void(QWidget*)> repolish =[](QWidget *w){
    // 卸掉再装载，等于刷新qss
    w->style()->unpolish(w);
    w->style()->polish(w);
};
