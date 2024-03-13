#include "ClickableCard.h"
#include <QMouseEvent>


ClickableCard::ClickableCard(Card card): card(card)
{
    image = new QPixmap(card.imagePath_small);
    this->setPixmap(image->scaled(45,190,Qt::KeepAspectRatio));
}

ClickableCard::~ClickableCard()
{
    delete image;
}

void ClickableCard::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit addToSideDeck(card.cardId);
    }
    if(event->button() == Qt::RightButton){
        emit removeCardFromDeck(card.cardId);
    }
}

void ClickableCard::enterEvent(QEnterEvent *event)
{
    emit(cardClicked(card.cardId));
}
