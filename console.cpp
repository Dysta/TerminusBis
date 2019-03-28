#include "console.h"

Console::Console(QWidget* parent)
    : QPlainTextEdit(parent), _cursorPos(0)
{
    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    this->setPalette(p);

    this->appendHtml(this->_html);
}

// override function for disable mouse click event
void Console::mousePressEvent(QMouseEvent *e) {
    Q_UNUSED(e);
}

// override function for disable mouse double click event
void Console::mouseDoubleClickEvent(QMouseEvent *e) {
    Q_UNUSED(e);
}

void Console::keyPressEvent(QKeyEvent *e) {

    if (e->matches(QKeySequence::SelectAll))
        return;

    switch (e->key()) {

    case Qt::Key_Left:
        if (this->_cursorPos > 0){
            this->_cursorPos--;
            QPlainTextEdit::keyPressEvent(e);
        }
        break;
    case Qt::Key_Right:
        if (this->_cursorPos < this->_buffer.size()) this->_cursorPos++;
        QPlainTextEdit::keyPressEvent(e);
        break;
    case Qt::Key_Up:
        std::cout << "key up" << std::endl;
        break;
    case Qt::Key_Down:
        std::cout << "key down" << std::endl;
        break;

    case Qt::Key_Backspace:
        if (this->_buffer.size() > 0 && this->_cursorPos > 0) {
            this->_buffer = this->_buffer.remove(this->_cursorPos -1, 1);
            this->_cursorPos--;
            QPlainTextEdit::keyPressEvent(e);
        }

        break;
    case Qt::Key_Delete:
        if (this->_buffer.size() > 0) {
            this->_buffer = this->_buffer.remove(this->_cursorPos, 1);
            QPlainTextEdit::keyPressEvent(e);
        }
        break;

    case Qt::Key_Return:
    case Qt::Key_Enter:
        // appel a parserInputrr
        // ajout du buffer dans l'historique
        this->_buffer.clear();
        this->_cursorPos = 0;
        this->appendHtml(this->_html);
        break;

    default:
        QByteArray key(e->text().toStdString().c_str());
        this->_buffer.insert(this->_cursorPos, key);
        this->_cursorPos++;
        QPlainTextEdit::keyPressEvent(e);
        break;

    }

    qDebug() << this->_buffer;
    qDebug() << "buffer size: " << this->_buffer.size();
    qDebug() << "current cursor pos: " << this->_cursorPos;
}
