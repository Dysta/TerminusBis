#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _edit(false)
{
    ui->setupUi(this);
    this->setWindowTitle("Terminus 2k29");

    this->_mainWidget = new QWidget(this);
    this->_grid = new QGridLayout(this->_mainWidget);

    this->createTerminal("Terminal");

    this->_mainWidget->setLayout(this->_grid);
    this->setCentralWidget(this->_mainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createTerminal(QString title) {
    this->_terminalBox = new QGroupBox(title);
    this->_terminal = new QPlainTextEdit(this->_terminalBox);

    this->_terminal->appendHtml(this->_html);
    this->_terminal->setStyleSheet("background-color:black; color: white;");

    connect(this->_terminal, SIGNAL(blockCountChanged(int)),
            this, SLOT(onBlockCountChanged(int)));

    this->_grid->addWidget(this->_terminalBox, 0, 0);
}

void MainWindow::onBlockCountChanged(int newBlockCount) {
    this->_edit = !this->_edit;
    if (this->_edit) {
        std::cout << "new count" << newBlockCount << std::endl;
        //this->_terminal->clear();
        this->_terminal->appendHtml(this->_html);
        std::cout << "end" << std::endl;
    }
}
