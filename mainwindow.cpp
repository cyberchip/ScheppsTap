#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStyle>
#include <QDesktopWidget>
#include <QDir>
#include <QPixmap>
#include <QBitmap>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    _path=QDir::homePath();
    if (_path.left(_path.length()-1)!="/")
        _path+="/ScheppsTap/";

    _settings   =new QSettings(_path+"configuracoes.ini", QSettings::IniFormat);
    _settingsTap=new QSettings(_path+"tap.ini"          , QSettings::IniFormat);

    this->setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    this->size(),
                    qApp->desktop()->availableGeometry()
                    )
                );

    if (_settings->value("Tela/FullScreen","Sim").toString().toLatin1().toLower()=="sim"){
        this->showFullScreen();
        _settings->setValue("Tela/FullScreen","Sim");
    }else{
        _settings->setValue("Tela/FullScreen","Nao");
    }

     QTimer::singleShot(200, this, SLOT(updateCaption()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCaption()
{
    ui->lblLogoCervejaria->clear();
    QPixmap pixmapCervejaria;
    if (pixmapCervejaria.load(_path+"TapLogoCervejaria.png")){
        ui->lblLogoCervejaria->setScaledContents( false );
        ui->lblLogoCervejaria->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        ui->lblLogoCervejaria->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        if (ui->lblLogoCervejaria->height()>ui->lblLogoCervejaria->width()){
            pixmapCervejaria = pixmapCervejaria.scaledToWidth ( ui->lblLogoCervejaria->width()  );
        }else{
            pixmapCervejaria = pixmapCervejaria.scaledToHeight( ui->lblLogoCervejaria->height() );
        }
        ui->lblLogoCervejaria->setPixmap(pixmapCervejaria);
    }

    ui->lblLogoCerveja->clear();
    QPixmap pixmapCerveja;
    if (pixmapCerveja.load(_path+"TapLogoCerveja.png")){
        ui->lblLogoCerveja->setScaledContents( false );
        ui->lblLogoCerveja->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        ui->lblLogoCerveja->setAlignment( Qt::AlignHCenter | Qt::AlignVCenter );
        if (ui->lblLogoCerveja->height()>ui->lblLogoCerveja->width()){
            pixmapCerveja = pixmapCerveja.scaledToWidth ( ui->lblLogoCerveja->width()  );
        }else{
            pixmapCerveja = pixmapCerveja.scaledToHeight( ui->lblLogoCerveja->height() );
        }
        ui->lblLogoCerveja->setPixmap(pixmapCerveja);
    }

    ui->lblCervejaria->setText( _settingsTap->value("Tap/Cervejaria","").toString().toLatin1() );
    ui->lblNome->setText( _settingsTap->value("Tap/Nome","").toString().toLatin1() );
    ui->lblTipo->setText( _settingsTap->value("Tap/Tipo","").toString().toLatin1() );
    ui->lblOrigem->setText( _settingsTap->value("Tap/Origem","").toString().toLatin1() );

    qDebug()<<_settingsTap->value("Tap/Descricao","");
    qDebug()<<_settingsTap->value("Tap/Descricao","").toString().toLatin1();

    ui->lblDescricao->setText( _settingsTap->value("Tap/Descricao","").toString().toLatin1() );
    ui->lblPreco->setText( _settingsTap->value("Tap/Preco","").toString().toLatin1() );
    ui->lblABV->setText( _settingsTap->value("Tap/ABV","").toString().toLatin1() );
    ui->lblIBU->setText( _settingsTap->value("Tap/IBU","").toString().toLatin1() );

}
