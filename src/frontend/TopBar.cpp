#include <QMessageBox>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include "TopBar.h"
#include "ui_TopBar.h"

TopBar::TopBar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TopBar)
{
    ui->setupUi(this);

    SetupTopBar();
    SetupPopupMenus();
}

TopBar::~TopBar()
{
    delete ui;
}

void TopBar::SetupTopBar() {
  this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
  this->setFixedSize(QSize(this->width(), this->height()));
}

void TopBar::SetupPopupMenus() {
  // Layout Popup Menu
  layoutMenu = new QMenu(this);
  layoutMenu->addSeparator();
  layoutMenuInstall = new QAction("Install a layout", this);
  layoutMenu->addAction(layoutMenuInstall);

  // Quit Popup Menu
  quitMenuQuit = new QAction("Quit", this);
  connect(quitMenuQuit, SIGNAL(triggered()), this, SLOT(quitMenuQuit_clicked()));
  quitMenu = new QMenu(this);
  quitMenu->addAction(quitMenuQuit);
}

void TopBar::quitMenuQuit_clicked() {
  TopBar::close();
}

void TopBar::on_buttonAbout_clicked()
{
    QMessageBox::about(this, "About OpenBangla Keyboard",
        tr("<h2>OpenBangla Keyboard 0.1</h2>"
        "<p>Copyright &copy; 2015-2016 Muhammad Mominul Huque & OpenBangla Team."
        "<p>An OpenSource, Cross-Platform, Unicode Compliant Bengali Input Method."));
}

void TopBar::mouseMoveEvent(QMouseEvent *event) {
  if(canMoveTopbar) {
    this->setCursor(Qt::ClosedHandCursor);
    move(event->globalX() - pressedMouseX, event->globalY() - pressedMouseY);
  }
}

void TopBar::mousePressEvent(QMouseEvent *event) {
  canMoveTopbar = true;
  pressedMouseX = event->x();
  pressedMouseY = event->y();
  event->accept();
}

void TopBar::mouseReleaseEvent(QMouseEvent *event) {
  canMoveTopbar = false;
  this->unsetCursor();
  event->accept();
}

void TopBar::on_buttonSetLayout_clicked()
{
  QPoint point;
  point = this->pos();
  point.setX(point.x() + ui->buttonSetLayout->geometry().x());
  point.setY(point.y() + this->height());
  layoutMenu->exec(point);
}

void TopBar::on_buttonShutdown_clicked()
{
    QPoint point;
    point = this->pos();
    point.setX(point.x() + ui->buttonShutdown->geometry().x());
    point.setY(point.y() + this->height());
    quitMenu->exec(point);
}