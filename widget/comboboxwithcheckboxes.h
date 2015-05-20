#ifndef COMBOBOXWITHCHECKBOXES_H
#define COMBOBOXWITHCHECKBOXES_H


#include <QComboBox>
#include <QEvent>

class ComboBoxWithCheckboxes : public QComboBox
{
    Q_OBJECT
public:
    ComboBoxWithCheckboxes(QWidget *parent = 0);
    ~ComboBoxWithCheckboxes();

signals:
    void checkboxClicked(bool checked);

private:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // COMBOBOXWITHCHECKBOXES_H
