#ifndef ITEMDETECTEDVIEW_H
#define ITEMDETECTEDVIEW_H


class ItemDetectedView : public QWidget
{
    Q_OBJECT
public:
    ItemDetectedView(QWidget *parent, const QPixmap&);

    QPixmap GetPixmap();
    void SetPixmap(const QPixmap& pixmap);
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
protected:
    // Override context menu event handler
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    QPixmap mPixmap;
    // Helper method to create the context menu
    void createContextMenu();
signals:
    void leftClicked();
    void rightClicked();
    void doubleClicked();
};

#endif // ITEMDETECTEDVIEW_H
