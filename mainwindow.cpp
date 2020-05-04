#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <map>
void MainWindow::addSquare(int x, int y)
{
    for(int d=0; d<2; d++)
    {
        segments.insert(Segment(QPoint(x+d, y), Segment::right));
        segments.insert(Segment(QPoint(x+d, y+2), Segment::right));

        segments.insert(Segment(QPoint(x, y+d), Segment::down));
        segments.insert(Segment(QPoint(x+2, y+d), Segment::down));
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas = findChild<QGraphicsView*>("canvas");
    canvas->setScene(&scene);

    for(int x=0; x<=6; x+=2)
    {
        for(int y=0; y<=6; y+=2)
            addSquare(x,y);
    }

    addSquare(1,1);
    addSquare(3,3);
    addSquare(5,5);

    std::cout << "size=" << segments.size() << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::run()
{
    QColor color(0,0,0);
    QPen pen(color, 2);

    scene.clear();

    for(const auto& segment: segments)
    {
        segment.draw(scene, pen);
    }

    count();
}

bool MainWindow::hasSegment(int x, int y, Segment::Dir dir) const
{
    Segment srch(QPoint(x,y), dir);

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

void MainWindow::count() const
{
    std::map<int, int> counter;     // [size] = count;
    for(int x=0; x<=7; x++)
    {
        for(int y=0; y<=7; y++)
        {
            for(int size=1; size<=8; size++)
            {
                counter[size] += hasSquare(x,y,size);
            }
        }
    }
    long total=0;
    for(const auto& p: counter)
    {
        std::cout << p.first << " -> " << p.second << std::endl;
        total += p.second;
    }
    std::cout << "TOTAL " << total << std::endl;
}
