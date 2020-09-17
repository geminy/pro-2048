#include "Controller.h"
#include "Config.h"

#include <QApplication>
#include <QtQml>
#include <QQuickView>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /* registers C++ type for qml */
    qmlRegisterType<Controller>("Models", 1, 0, "Controller");

    QQuickView view;

    /* title */
    view.setTitle(WINDOW_TITLE);

    /* icon */
    view.setIcon(QIcon(WINDOW_ICON));

    /* layout */
    QDesktopWidget *desktop = QApplication::desktop();
    Q_ASSERT(desktop);
    int desktopWidth = desktop->screenGeometry().width();
    int desktopHeight = desktop->screenGeometry().height();
    Q_ASSERT(desktopWidth >= WINDOW_SIZE_WIDTH);
    Q_ASSERT(desktopHeight >= WINDOW_SIZE_HEIGHT);
    int xPos = (desktopWidth - WINDOW_SIZE_WIDTH) / 2;
    int yPos = (desktopHeight - WINDOW_SIZE_HEIGHT) / 2;
    view.setGeometry(xPos, yPos, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
    view.setResizeMode(QQuickView::SizeViewToRootObject);
    view.setMaximumSize(QSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT));
    view.setMinimumSize(QSize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT));

    /*set window size for qml */
    view.rootContext()->setContextProperty("appWinWidth", WINDOW_SIZE_WIDTH);
    view.rootContext()->setContextProperty("appWinHeight", WINDOW_SIZE_HEIGHT);

    /* home view */
    view.setSource(QUrl(QStringLiteral(QML_HOME)));
    view.show();

    return app.exec();
}
