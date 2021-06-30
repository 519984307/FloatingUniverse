#include <QVBoxLayout>
#include <QIcon>
#include "panelitem.h"
#include "usettings.h"
#include "runtime.h"

PanelItem::PanelItem(QWidget *parent) : QWidget(parent)
{
    iconLabel = new QLabel(this);
    textLabel = new QLabel(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);

    iconLabel->setScaledContents(false);
    iconLabel->setAlignment(Qt::AlignCenter);
    textLabel->setAlignment(Qt::AlignCenter);

    selectWidget = new QWidget(this);
    selectWidget->hide();
    selectWidget->setStyleSheet("background: transparent; border: " + QString::number(selectBorder) + "px solid #FF0000");
}

MyJson PanelItem::toJson() const
{
    MyJson json;

    QRect rect(this->geometry());
    json.insert("left", rect.left());
    json.insert("top", rect.top());
    json.insert("width", rect.width());
    json.insert("height", rect.height());

    json.insert("icon", "");
    json.insert("text", textLabel->text());

    if (link.isEmpty())
        json.insert("link", link);

    return json;
}

PanelItem *PanelItem::fromJson(const MyJson &json, QWidget *parent)
{
    PanelItem* item = new PanelItem(parent);

    // 位置
    QRect rect(json.i("left"), json.i("top"), json.i("width"), json.i("height"));
    item->move(rect.topLeft());

    // 基础数据
    QString iconName = json.s("icon");
    item->setIcon(iconName);
    item->setText(json.s("text"));

    // 扩展数据
    item->link = json.s("link");

    return item;
}

void PanelItem::setIcon(const QString &iconName)
{
    if (iconName.isEmpty())
        return ;
    QIcon icon(rt->ICON_PATH + iconName);
    if (!icon.isNull())
        iconLabel->setPixmap(icon.pixmap(us->pannelItemSize, us->pannelItemSize));
}

void PanelItem::setText(const QString &text)
{
    textLabel->setText(text);
    this->text = text;
}

void PanelItem::setLink(const QString &link)
{
    this->link = link;
}

void PanelItem::showSelect(bool sh)
{
    if (sh)
    {
        selectWidget->setGeometry(selectBorder / 2, selectBorder / 2, width() - selectBorder, height() - selectBorder);
        selectWidget->raise();
        selectWidget->show();
    }
    else
    {
        selectWidget->hide();
    }
}
