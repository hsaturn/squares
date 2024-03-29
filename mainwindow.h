#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <set>

#include <QMainWindow>
#include <QGraphicsView>
#include <QListView>

#include <segment.h>
#include <iostream>

namespace Ui {
class MainWindow;
}

struct SegCompare
{
    bool operator()(const Segment& lhs, const Segment& rhs) const
    {
        long h1 = lhs.hash();
        long h2 = rhs.hash();

        return h1 < h2;

        // Comprend pas, j'ai implémenté compare et ça ne marche pas avec ça
        // https://en.cppreference.com/w/cpp/named_req/Compare
        if (h1 == h2)
        {
            return false;

        }
        else
            return true;
    }
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addSquare(int x, int y, QPen& pen, int segPerSide=2);
    void count() const;
    int hasSquare(int x, int y, int size) const;
    bool hasSegment(int x, int y, Segment::Dir) const;

public slots:
    void create();
    void solve() const;
    void redraw(int zoom = -1);
    void reset();

private:
    Ui::MainWindow *ui;
    QGraphicsView* canvas;
    QListView* results;
    QGraphicsScene scene;

    std::set<Segment, SegCompare> segments;
    int zoom;
};

#endif // MAINWINDOW_H
