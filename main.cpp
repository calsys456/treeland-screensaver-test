#include <QDBusInterface>
#include <QDBusReply>

int main(int argc, char *argv[])
{
    system("pkill -f /usr/libexec/treeland-screensaver"); // Ensure no previous instance is running
    const QString busName("treeland-screensaver-test");
    {
        auto conn = QDBusConnection::connectToBus(QDBusConnection::SessionBus, busName);
        QDBusInterface interface("org.freedesktop.ScreenSaver",
                                 "/org/freedesktop/ScreenSaver",
                                 "org.freedesktop.ScreenSaver",
                                 conn);
        if (interface.isValid())
            qInfo() << "Connected to org.freedesktop.ScreenSaver.";
        else
            qFatal() << "Failed to connect to org.freedesktop.ScreenSaver:"
                     << QDBusConnection::sessionBus().lastError().message();

        QDBusReply<uint> reply1 = interface.call("Inhibit", "treeland-screensaver-test", "Testing inhibit/uninhibit");
        uint cookie;
        if (reply1.isValid()) {
            cookie = reply1.value();
            qInfo() << "Inhibit once. Cookie:" << cookie;
        } else {
            qFatal() << "Failed to call Inhibit:" << reply1.error().message();
        }

        QDBusReply<void> reply2 = interface.call("UnInhibit", cookie);
        if (reply2.isValid()) {
            qInfo() << "UnInhibit cookie" << cookie;
        } else {
            qFatal() << "Failed to UnInhibit cookie 1:" << reply2.error().message();
        }

        sleep(0.1);
        if (system("pgrep -fx /usr/libexec/treeland-screensaver > /dev/null") != 0) {
            qInfo() << "treeland-screensaver has exited as expected.";
        } else {
            system("ps -p $(pgrep -fx /usr/libexec/treeland-screensaver)");
            qFatal() << "treeland-screensaver is still running unexpectedly.";
        }

        QDBusReply<uint> reply3 = interface.call("Inhibit", "treeland-screensaver-test", "Testing inhibit/uninhibit");
        uint cookie1;
        if (reply3.isValid()) {
            cookie1 = reply3.value();
            qInfo() << "Inhibit once. Cookie:" << cookie1;
        } else {
            qFatal() << "Failed to call Inhibit:" << reply3.error().message();
        }

        QDBusReply<uint> reply4 = interface.call("Inhibit", "treeland-screensaver-test", "Testing inhibit/uninhibit");
        uint cookie2;
        if (reply4.isValid()) {
            cookie2 = reply4.value();
            qInfo() << "Inhibit twice. Cookie:" << cookie2;
        } else {
            qFatal() << "Failed to call Inhibit at second time:" << reply4.error().message();
        }

        QDBusReply<void> reply5 = interface.call("UnInhibit", cookie1);
        if (reply5.isValid()) {
            qInfo() << "UnInhibit cookie" << cookie1;
        } else {
            qFatal() << "Failed to UnInhibit cookie 1:" << reply5.error().message();
        }
    }
    qInfo() << "Disconnecting from D-Bus to test automatic uninhibit...";
    QDBusConnection::disconnectFromBus(busName); // Simulate client disconnection
    sleep(0.1); // Wait a moment for the screensaver to exit
    if (system("pgrep -fx /usr/libexec/treeland-screensaver > /dev/null") != 0) {
        qInfo() << "treeland-screensaver has exited as expected.";
    } else {
        system("ps -p $(pgrep -fx /usr/libexec/treeland-screensaver)");
        qFatal() << "treeland-screensaver is still running unexpectedly.";
    }
    qInfo() << "Success.";
    return 0;
}
