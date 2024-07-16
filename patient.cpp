#include "patient.h"
#include "qdebug.h"
#include <QFile>
#include <QTextStream>
#include <QIODevice>


void patient::saveAppointments()
{
    QString fileName = "Appointments.txt";
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&file);

        // Iterate through appointments and write to file
        for (auto it = appointments.constBegin(); it != appointments.constEnd(); ++it) {
            QString line = username + ":" + it.key() + ":" + it.value() + "\n";
            out << line;
        }

        file.close();
    } else {
        qDebug() << "Failed to open file for writing:" << file.errorString();
    }
}




void patient::loadAppointments() {
    QFile file("Appointments.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() == 3 && parts[0] == name) {
                appointments[parts[1]] = parts[2];
            }
        }
        file.close();
    }
}


patient::patient() {

}
void patient::setusername(QString username){
    name=username;
}
patient::patient(QString n, QString p, int a, QString g){
    name=n;
    age=a;
    pass=p;
    gender=g;
}
