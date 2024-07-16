#ifndef BOOKAPPOINTMENTWINDOW_H
#define BOOKAPPOINTMENTWINDOW_H
#include "drclass.h"
#include "qlistwidget.h"
#include <QDialog>
#include "patient.h"
namespace Ui {
class BookAppointmentWindow;
}

class BookAppointmentWindow : public QDialog
{
    Q_OBJECT

public:
    explicit BookAppointmentWindow(QWidget *parent = nullptr,patient p=patient());
    ~BookAppointmentWindow();
    drclass* findDoctorByUsername(const QString& username);

private slots:
    void clearSlotsList();
    void addSlotToList(const QString &slot);
    void on_radioButton_Nutrition_clicked();

    void on_radioButton_OG_clicked();

    void on_radioButton_Ophthalmology_clicked();

    void on_radioButton_internalmedicine_clicked();

    void on_radioButton_Dermatology_clicked();

    void on_slotsListView_itemClicked(QListWidgetItem *item);

    //void on_pushButtonSubmit_clicked(bool checked);

   void on_pushButtonSubmit_clicked();


private:
    Ui::BookAppointmentWindow *ui;
    patient currpat;
    //bool submitClicked = false; // Add this flag
};

#endif // BOOKAPPOINTMENTWINDOW_H
