#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <map>
#include <QStringListModel>
#include <stdlib.h>

void MainWindow::addSquare(int x, int y, QPen& pen, int size)
{
    static int minx=999;
    static int miny=999;
    if (x < minx)
    {
        minx=x;
        std::cout << "minx=" << minx << std::endl;
    }
    if (y < miny)
    {
        miny=y;
        std::cout << "miny" << miny << std::endl;
    }
    for(int d=0; d<size; d++)
    {
        segments.insert(Segment(QPoint(x+d, y), Segment::right, pen));
        segments.insert(Segment(QPoint(x+d, y+size), Segment::right, pen));

        segments.insert(Segment(QPoint(x, y+d), Segment::down, pen));
        segments.insert(Segment(QPoint(x+size, y+d), Segment::down, pen));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    zoom(10)
{
    ui->setupUi(this);
    canvas = findChild<QGraphicsView*>("canvas");
    results = findChild<QListView*>("results");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::reset()
{
    segments.clear();
    redraw();
}

void MainWindow::create()
{

    QPen color1(QColor(255,0,0), 2);
    QPen color2(QColor(0,0,255), 2);
    canvas->setScene(&scene);

    /*    for(int x=0; x<=6; x+=2)
    {
        for(int y=0; y<=6; y+=2)
            addSquare(x,y, color1);
    }
    addSquare(1,1, color2);
    addSquare(3,3, color2);
    addSquare(5,5, color2);

*/

    int max = 3;
    for(int i=0; i<=3; i++)
    {
        int x = rand() % max;
        int y = rand() % max;
        int size = 2+rand()%2;

        addSquare(x, y, color1, size);
        addSquare(max-x-size, y, color1, size);
        addSquare(x, max-y-size, color1, size);
        addSquare(max-x-size, max-y-size, color1, size);
    }

    redraw();
}

void MainWindow::redraw(int newZoom)
{
    if (newZoom != -1)
    {
        zoom=newZoom;
    }
    Segment::setScale(zoom);

    QColor color(0,0,0);
    QPen pen(color, 2);

    scene.clear();

    for(const auto& segment: segments)
    {
        segment.draw(scene);
    }
    results->setModel(new QStringListModel());

}

bool MainWindow::hasSegment(int x, int y, Segment::Dir dir) const
{
    static QPen dummy;
    Segment srch(QPoint(x,y), dir, dummy);

    for(const Segment& seg: segments)
    {
        if (seg.hash() == srch.hash())
            return true;
    }
    return false;
    // TODO pkoi ça ne fonctionne pas ça (décdément les set...)
    // return segments.find(srch) != segments.end();
}

int MainWindow::hasSquare(int x, int y, int size) const
{
    for(int i=0; i<size; i++)
    {
        if (!hasSegment(x+i, y, Segment::right)) return false;
        if (!hasSegment(x+i, y+size, Segment::right)) return false;

        if (!hasSegment(x, y+i, Segment::down)) return false;
        if (!hasSegment(x+size, y+i, Segment::down)) return false;
    }
    return true;
}

struct QPointCompare
{
    bool operator() (const QPoint& x, const QPoint& y)
    {
        return (x.x()*100+x.y()) < (y.x()*100+y.y());
    }
};

void MainWindow::solve() const
{
    QStringList list;
    std::set<QPoint, QPointCompare > points;

    for(const auto& segment: segments)
    {
        points.insert(segment.start());
    }

    std::map<int, int> counter;     // [size] = count;

    for(const QPoint& point: points)
    {
        for(int size=1; size<=20; size++)
        {
            counter[size] += hasSquare(point.x(), point.y(), size);
        }
    }
    /*
    for(int x=-5; x<=30; x++)
    {
        for(int y=-5; y<=30; y++)
        {
            for(int size=1; size<=20; size++)
            {
                counter[size] += hasSquare(x,y,size);
            }
        }
    }
    */
    long total=0;
    for(const auto& p: counter)
    {
        if (p.second)
            list.append(QString::number(p.first)+QString(" -> ")+QString::number(p.second));

        total += p.second;
    }
    list.append(QString("Total: ")+QString::number(total));
    results->setModel(new QStringListModel(list));

}
