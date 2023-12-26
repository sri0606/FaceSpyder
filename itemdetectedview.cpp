#include "pch.h"
#include "itemdetectedview.h"
#include <QLabel>
#include <QLayout>
#include <QMenu>
ItemDetectedView::ItemDetectedView(QWidget *parent,const QPixmap& pixmap)
    : QWidget{parent}
{
    mPixmap = pixmap;
    setAutoFillBackground(true);
    QLabel* imageLabel = new QLabel(this);
    imageLabel->setAlignment(Qt::AlignCenter);  // Center the pixmap in the widget
    auto layout = new QVBoxLayout(this);
    layout->addWidget(imageLabel);

    // Ensure that the context menu policy is set to enable contextMenuEvent
    setContextMenuPolicy(Qt::CustomContextMenu);

    // Connect the customContextMenuRequested signal to the method that creates the context menu
    connect(this, &ItemDetectedView::customContextMenuRequested, this, &ItemDetectedView::createContextMenu);
}

void ItemDetectedView::contextMenuEvent(QContextMenuEvent* event)
{
    Q_UNUSED(event);
    // The context menu will be created in the createContextMenu method
}

void ItemDetectedView::createContextMenu()
{
    QMenu contextMenu(this);

    // Add actions to the context menu
    QAction* action1 = contextMenu.addAction("Option 1");
    QAction* action2 = contextMenu.addAction("Option 2");
    QAction* action3 = contextMenu.addAction("Option 3");

    // Show the context menu and get the selected action
    QAction* selectedAction = contextMenu.exec(QCursor::pos());

    // Process the selected action
    if (selectedAction) {
        if (selectedAction == action1) {
            // Handle Option 1
        } else if (selectedAction == action2) {
            // Handle Option 2
        } else if (selectedAction == action3) {
            // Handle Option 3
        }
    }
}

QPixmap ItemDetectedView::GetPixmap(){
    return mPixmap;
}

void ItemDetectedView::SetPixmap(const QPixmap& pixmap) {

    QLabel* imageLabel = findChild<QLabel*>();
    if (imageLabel) {
        imageLabel->setPixmap(pixmap);
    }

}

void ItemDetectedView::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit leftClicked();
    } else if (event->button() == Qt::RightButton) {
        emit rightClicked();
    }

    // Pass the event to the base class implementation
    QWidget::mousePressEvent(event);
}

void ItemDetectedView::mouseReleaseEvent(QMouseEvent* event)
{

    // Pass the event to the base class implementation
    QWidget::mouseReleaseEvent(event);
}

void ItemDetectedView::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        emit doubleClicked();
    }

    // Pass the event to the base class implementation
    QWidget::mouseDoubleClickEvent(event);
}
