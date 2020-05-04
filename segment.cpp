#include "segment.h"

int Segment::scale_ = 20;

void Segment::draw(QGraphicsScene& scene, const QPen& pen) const
{
    int sx=-100;
    int sy=-100;

    int dx=0, dy=0;
    if (_dir == right)
    {
        dx=scale_;
    }
    else
    {
        dy = scale_;
    }
    scene.addLine(_start.x()*scale_+sx,_start.y()*scale_+sy,
                  _start.x()*scale_+sx+dx,_start.y()*scale_+sy+dy,
                  pen);
}
