#include <QApplication>
#include "BeaconControlCenter.h"
#include  "FramelessWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeaconControlCenter centerWidget;

    // 创建无边框、圆角、有阴影、可拖动的窗口
    FramelessWindow *window = new FramelessWindow(&centerWidget);
    window->setTitleBarButtonsVisible(true, false, true);
    window->setTitle("Beacon控制中心");
//    window->setTitleBarVisible(false);
    window->resize(centerWidget.width()+10, centerWidget.height()+30);
    window->setResizable(false);
    window->show();
    //退出应用程序
    QObject::connect(&centerWidget,SIGNAL(closeTitle()),window,SLOT(close()));
    return a.exec();
}
