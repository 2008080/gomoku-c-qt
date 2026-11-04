#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initBoard(board);
    currentPlayer = BLACK;
    setFixedSize(600, 600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(200, 150, 100));
    int grid = 40;
    for (int i = 0; i < BOARD_SIZE; i++) {
        painter.drawLine(grid, grid + i * grid, grid + 14 * grid, grid + i * grid);
        painter.drawLine(grid + i * grid, grid, grid + i * grid, grid + 14 * grid);
    }
    // 绘制棋子
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == BLACK) {
                painter.setBrush(Qt::black);
                painter.drawEllipse(QPoint(grid + i*grid, grid + j*grid), 18, 18);
            } else if (board[i][j] == WHITE) {
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(grid + i*grid, grid + j*grid), 18, 18);
            }
        }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int grid = 40;
    int x = qRound((event->pos().x() - grid) / (double)grid);
    int y = qRound((event->pos().y() - grid) / (double)grid);
    if (placePiece(board, x, y, currentPlayer)) {
        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
        update();
    }
}