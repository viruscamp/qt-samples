#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "qdebug.h"
#include <QApplication>
#include <QTextEdit>
#include <QEvent>
#include <QKeyEvent>
#include <QStyle>

#include <fmt/core.h>
#include <fmt/format.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	
	this->setFixedSize(this->width(), this->height());
	this->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::WindowStaysOnTopHint);

	auto app = dynamic_cast<QGuiApplication*>(QGuiApplication::instance());
	QString title = "Qt Sample 1 - Qt" QT_VERSION_STR "@" + app->platformName();
	this->setWindowTitle(title);
	
	//ui->lineEditCnt->setEnabled(false);
	ui->lineEditCnt->setReadOnly(true);
	ui->lineEditCnt->setFocusPolicy(Qt::FocusPolicy::NoFocus); //让它无法获取焦点
	
	// 按钮无法获取焦点时, 仍然可以正常用鼠标点击, 只是不能用键盘导航
	ui->pushButtonCntUp->setFocusPolicy((Qt::FocusPolicy::NoFocus)); 
	ui->pushButtonCntDn->setFocusPolicy((Qt::FocusPolicy::NoFocus));
	ui->pushButtonCntRst->setFocusPolicy((Qt::FocusPolicy::NoFocus));
	
	flushCntNumber();
}

MainWindow::~MainWindow()
{
	//delete textEdit;
	delete ui;
}

void MainWindow::setCntNumber(int number, bool isFlush)
{
	m_number = number;
	if(isFlush){
		flushCntNumber();
	}
}

void MainWindow::flushCntNumber()
{
	ui->lineEditCnt->setText(QString::number(m_number));
	ui->lineEditCnt->setText(QString::fromStdString(fmt::format("{}", m_number)));
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{	
	switch (int key = ev->key(); key){ //(ev->key() & 0xFFFF)
		case Qt::Key::Key_Up:
		case Qt::Key_U:
		case Qt::Key_Space:
		case Qt::Key_Return:
			btnCntUp_Click();			
			break;
		case Qt::Key::Key_Down:
		case Qt::Key::Key_D:
		case Qt::Key::Key_Backspace:
			btnCntDn_Click();			
			break;
		case Qt::Key::Key_R:
		case Qt::Key::Key_Delete:
			btnCntRst_Click();			
			break;
		default:
			fmt::println("keyPressEvent, key=0x{:x}", key);
	}
	
}

void MainWindow::btnCntDn_Click()
{
	m_number--;
	flushCntNumber();
}

void MainWindow::btnCntRst_Click()
{
	m_number = 0;
	flushCntNumber();
	ui->lineEditCnt->text();
}

void MainWindow::btnCntUp_Click()
{
	m_number++;
	flushCntNumber();
}

void MainWindow::btnIcon_Click()
{
	const QSize iconSize(22,22);
	auto iconName = ui->plainTextEditIcon->toPlainText();
	auto icon = QIcon::fromTheme(iconName);
	qDebug() << "theme: " << QIcon::themeName() << " name: " << icon.name();
	qDebug() << "QIcon::hasThemeIcon(" << iconName << ") = " << QIcon::hasThemeIcon(iconName);
	if (icon.isNull()) {
		icon = QApplication::style()->standardIcon(QStyle::SP_MediaVolume);
	}
	
	ui->pushButtonIcon->setIcon(icon.pixmap(iconSize));
}
