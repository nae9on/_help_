#include <QApplication>

#include <QDesktopWidget>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;

    QLabel *queryLabel = new QLabel(
        QApplication::translate("nestedlayouts", "Query:"));
    QLineEdit *queryEdit = new QLineEdit();
    QTableView *resultView = new QTableView();

    QStandardItemModel model;
    model.setHorizontalHeaderLabels({ QApplication::translate("nestedlayouts", "Name"),
                                      QApplication::translate("nestedlayouts", "Office") });

    const QStringList rows[] = {
        QStringList{ QStringLiteral("Verne Nilsen"), QStringLiteral("123") },
        QStringList{ QStringLiteral("Carlos Tang"), QStringLiteral("77") },
        QStringList{ QStringLiteral("Bronwyn Hawcroft"), QStringLiteral("119") },
        QStringList{ QStringLiteral("Alessandro Hanssen"), QStringLiteral("32") },
        QStringList{ QStringLiteral("Andrew John Bakken"), QStringLiteral("54") },
        QStringList{ QStringLiteral("Vanessa Weatherley"), QStringLiteral("85") },
        QStringList{ QStringLiteral("Rebecca Dickens"), QStringLiteral("17") },
        QStringList{ QStringLiteral("David Bradley"), QStringLiteral("42") },
        QStringList{ QStringLiteral("Knut Walters"), QStringLiteral("25") },
        QStringList{ QStringLiteral("Andrea Jones"), QStringLiteral("34") }
    };

    QList<QStandardItem *> items;
    for (const QStringList &row : rows) {
        items.clear();
        for (const QString &text : row)
            items.append(new QStandardItem(text));
        model.appendRow(items);
    }

    resultView->setModel(&model);
    resultView->verticalHeader()->hide();
    resultView->horizontalHeader()->setStretchLastSection(true);

    QHBoxLayout *queryLayout = new QHBoxLayout();
    queryLayout->addWidget(queryLabel);
    queryLayout->addWidget(queryEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(queryLayout);
    mainLayout->addWidget(resultView);
    window.setLayout(mainLayout);

    // Set up the model and configure the view...
    window.setWindowTitle(
        QApplication::translate("nestedlayouts", "Nested layouts"));
    window.show();

    return a.exec();
}
