#include "comboboxwithcheckboxes.h"

#include <QAbstractItemView>

ComboBoxWithCheckboxes::ComboBoxWithCheckboxes(QWidget *parent) : QComboBox(parent)
{
    view()->viewport()->installEventFilter(this);
}

ComboBoxWithCheckboxes::~ComboBoxWithCheckboxes()
{

}

bool ComboBoxWithCheckboxes::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == view()->viewport() &&  event->type() == QEvent::MouseButtonRelease) {
        emit checkboxClicked(itemData(view()->currentIndex().row(), Qt::CheckStateRole) == Qt::Unchecked);
    }
    return QObject::eventFilter(obj, event);
}
