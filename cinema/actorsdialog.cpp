#include "actorsdialog.h"

ActorsDialog::ActorsDialog(QStandardItemModel *modelItem,QString movieName, QWidget *parent)
     : QDialog(parent)
{
    ui.setupUi(this);
    model = modelItem;

    connect(ui.closeButton, SIGNAL(clicked()), this, SLOT(close()));

    ui.actorsGroupBox->setTitle("Актеры из фильма "+movieName);
    ui.tableView->setModel(modelItem);
    ui.tableView->hideColumn(2);
    ui.tableView->resizeColumnsToContents();
//    QTableView *inputWidgetBox = createInputWidgets();
//    QDialogButtonBox *buttonBox = createButtons();

//    QVBoxLayout *layout = new QVBoxLayout;
//    layout->addWidget(inputWidgetBox);
//    layout->addWidget(buttonBox);
//    setLayout(layout);


}




QTableView *ActorsDialog::createInputWidgets()
{
         QTableView* coilView = new QTableView(this); // create the tableview
    //       coilView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    //coilView->setItemDelegate(new ComboBoxDelegate(coilView));
    //      ui.actorsEdit->setView(coilView);
    //      ui.actorsEdit->setModel(model2);
    //      ui.actorsEdit->setEditable(true);
          coilView->setModel(model);
          coilView->resizeColumnsToContents();





    return coilView;
}

QDialogButtonBox *ActorsDialog::createButtons()
{
    QPushButton *closeButton = new QPushButton(tr("&Close"));
//    QPushButton *revertButton = new QPushButton(tr("&Revert"));
//    QPushButton *submitButton = new QPushButton(tr("&Submit"));

    closeButton->setDefault(true);

    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
//    connect(revertButton, SIGNAL(clicked()), this, SLOT(revert()));
//    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));

    QDialogButtonBox *buttonBox = new QDialogButtonBox;
//    buttonBox->addButton(submitButton, QDialogButtonBox::ResetRole);
//    buttonBox->addButton(revertButton, QDialogButtonBox::ResetRole);
    buttonBox->addButton(closeButton, QDialogButtonBox::RejectRole);

    return buttonBox;
}
