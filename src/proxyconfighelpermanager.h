#ifndef PROXYCONFIGHELPERMANAGER_H
#define PROXYCONFIGHELPERMANAGER_H

#include <QObject>

class ProxyConfigHelperManager: public QObject
{
public:
    ProxyConfigHelperManager();
    static void install();
    static void setUpSystemProxy(int port, int socksPort);
};

#endif // PROXYCONFIGHELPERMANAGER_H
