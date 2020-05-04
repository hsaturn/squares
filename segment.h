#pragma once
#include <QPoint>
#include <QPen>
#include <QGraphicsScene>

class Segment
{
    public:
        typedef enum
        {
            right = 1,
            down = 2
        } Dir;

        Segment(QPoint start, Dir dir) : _start(start), _dir(dir) {}

        void draw(QGraphicsScene&, const QPen&) const;

        long hash() const
        {
            return _dir * 1000000 + _start.x() * 512 + _start.y();
        }

        static void setScale(int scale) { scale_ = scale; }

    private:
        static int scale_;

        QPoint _start;
        Dir _dir;
};
