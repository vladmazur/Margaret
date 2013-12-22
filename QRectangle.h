#ifndef QRECTANGLE_H
#define QRECTANGLE_H

#include "Rectangle.h"
#include "qfigure.h"
#include <QPainter>

class QRectangle : public Rectangle, public QFigure
{
public:
    QRectangle();

    QRectangle(const Point& p1, const Point& p2) : Rectangle(p1, p2) {}
    virtual Line& getStyle();
    virtual const Line& getStyle() const
    {return Rectangle::getLine();}
    virtual Point getCenter() const
    {return Rectangle::getCenter(); }
    virtual Point getSize() const
    {return Point(Rectangle::getHeight(), Rectangle::getWidth()); }

    virtual void setBounds(const Point& p1, const Point& p2);
    virtual void move(const Point& destination);
    virtual bool belongs(const Point& point);
    virtual void draw(QPainter & painter) const
    {
        Point tl = Rectangle::center - Rectangle::size * 0.5;
        Color p = getStyle().lineColor;
        Color f = getStyle().fillColor;
        if (isSelected()) f.alpha = 0.5;
        painter.setPen(QColor(p.red * 255, p.green * 255, p.blue * 255, p.alpha * 255)); painter.setBrush(QBrush(QColor(f.red * 255, f.green * 255, f.blue * 255, f.alpha * 255))); painter.drawRect(tl.x, tl.y, Rectangle::size.x, Rectangle::size.y);
    }
    virtual void select(bool sel);
    virtual bool isSelected() const;
};

#endif // QRECTANGLE_H


//void QtRectangle::select(bool sel) {
//    QtShape2D::select(sel); }

//bool QtRectangle::isSelected() const {
//    return QtShape2D::isSelected(); }
//DrawStyle& QtRectangle::getStyle() {
//    return Rectangle::getStyle(); }
//const DrawStyle& QtRectangle::getStyle() const {
//    return Rectangle::getStyle(); }
//Point2D QtRectangle::getCenter() const {
//    return Rectangle::getCenter(); }
//Point2D QtRectangle::getSize() const {
//    return Rectangle::getSize(); }
void QtRectangle::setBounds(const Point2D& p1, const Point2D& p2) {
    Rectangle::setBounds(p1, p2); }
void QtRectangle::move(const Point2D& destination) {
    Rectangle::move(destination); }
bool QtRectangle::belongs(const Point2D& p) {
    return Rectangle::belongs(p); }
