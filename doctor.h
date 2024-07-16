#ifndef DOCTOR_H
#define DOCTOR_H
#include "drclass.h"
#include <QDialog>
#include "bookappointmentwindow.h"
namespace Ui {
class doctor;
}

class doctor : public QDialog
{
    Q_OBJECT

public:
    explicit doctor(QWidget *parent = nullptr, drclass dr = drclass());
    ~doctor();
    QString getAssignmentString(drclass& doc);

private slots:
    void on_pushButton_profile_clicked();

    void on_pushButton_profile_2_clicked();

    void on_pushButton_schedule_clicked();

    void on_pushButton_clicked();

private:
    Ui::doctor *ui;
    drclass currdoc;
};

#endif // DOCTOR_H
