#ifndef HIERARCHICALHEADERVIEW_H
#define HIERARCHICALHEADERVIEW_H


#include <QHeaderView>
#include <QEvent>

class HierarchicalHeaderView : public QHeaderView
{
    Q_OBJECT

    class private_data;
    private_data* _pd;

    QStyleOptionHeader styleOptionForCell(int logicalIndex) const;

protected:
    void paintSection(QPainter* painter, const QRect& rect, int logicalIndex) const;
    QSize sectionSizeFromContents(int logicalIndex) const;
    bool eventFilter(QObject *obj, QEvent *event);

public:

    enum HeaderDataModelRoles
        {HorizontalHeaderDataRole=Qt::UserRole,
         VerticalHeaderDataRole=Qt::UserRole+1};

    HierarchicalHeaderView(Qt::Orientation orientation, QWidget* parent = 0);
    ~HierarchicalHeaderView();

    void setModel(QAbstractItemModel* model);
private slots:
    void on_sectionResized(int logicalIndex);
    void on_entered(QModelIndex index);
};


#endif // HIERARCHICALHEADERVIEW_H
