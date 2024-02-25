#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QIcon>
#include <QPixmap>
#include <QStyleFactory>
#include <QHeaderView>
#include <qdebug.h>

#include "enum-utils.hpp"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto style = app.style();
#if (QT_VERSION >= QT_VERSION_CHECK(6,1,0))
    qDebug() << "current style: " << style->name();
#endif

    auto styleNames = QStyleFactory::keys();
    qDebug() << "available style: " << styleNames;

    QTableWidget tableWidget;

    const int count =  enum_max<QStyle::StandardPixmap>();

    tableWidget.setRowCount(count);
    tableWidget.setColumnCount(3 + styleNames.count());

    auto head0 = new QTableWidgetItem;
    head0->setText("Value");
    tableWidget.setHorizontalHeaderItem(0, head0);
    tableWidget.setColumnWidth(0, 40);

    auto head1 = new QTableWidgetItem;
    head1->setText("Name");
    tableWidget.setHorizontalHeaderItem(1, head1);
    tableWidget.setColumnWidth(1, 160);

    auto head2 = new QTableWidgetItem;
    head2->setText("Current");
    tableWidget.setHorizontalHeaderItem(2, head2);
    tableWidget.setColumnWidth(2, 80);

    tableWidget.verticalHeader()->setVisible(false);

    auto styles = QList<QStyle*>();
    for (int j = 0; j < styleNames.count(); j++) {
        auto styleName = styleNames[j];
        auto st = QStyleFactory::create(styleName);
        styles.append(st);

        auto head = new QTableWidgetItem;
        head->setText(styleName);
        tableWidget.setHorizontalHeaderItem(3 + j, head);
        tableWidget.setColumnWidth(3 + j, 80);
    }

    for (int i = 0; i < count; i++) {
        auto sp = QStyle::StandardPixmap(i);
        auto icon = style->standardIcon(sp);
        auto name = enum_name(sp);
        
        auto item_num = new QTableWidgetItem;
        item_num->setText(QString::number(i));
        tableWidget.setItem(i, 0, item_num);
        
        auto item_name = new QTableWidgetItem;
        item_name->setText(QString::fromUtf8(name.data(), name.size()));    	
        tableWidget.setItem(i, 1, item_name);

        auto item_icon = new QTableWidgetItem;
        item_icon->setIcon(icon);
        tableWidget.setItem(i, 2, item_icon);

        for (int j = 0; j < styles.count(); j++) {
            auto st = styles[j];
            auto icon = st->standardIcon(sp);
#if (QT_VERSION >= QT_VERSION_CHECK(6,1,0))
            qDebug() << st->name() << icon;
#endif

            auto item = new QTableWidgetItem;
            item->setIcon(icon);
            tableWidget.setItem(i, 3 + j, item);
        }
    }

    tableWidget.setMinimumWidth(680);
    tableWidget.setMinimumHeight(600);
    
    tableWidget.setWindowTitle("Qt" QT_VERSION_STR " QStyle::StandardPixmap");

    tableWidget.show();
 
    return app.exec();
}
