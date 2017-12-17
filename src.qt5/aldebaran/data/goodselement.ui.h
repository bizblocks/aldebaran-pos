/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/

#include <qvalidator.h>

void GoodsElement::selectPicture()
{
    QFileDialog fileDlg(QDir::currentDirPath(), "Images (*.png *.jpg *.bmp)");
    fileDlg.setCaption(tr("Open goods picture"));
    if(fileDlg.exec()==QDialog::Accepted)
	labelPicture->setPixmap(QPixmap::fromMimeSource(fileDlg.selectedFile()));
}

void GoodsElement::clearPicture()
{
    labelPicture->setPixmap(QPixmap());
}

void GoodsElement::setData(alGoodsRecord * data)
{
    fData = data;
    refresh();
}

void GoodsElement::refresh()
{
    if(!fData) return;
    parentGroup = fData->parent();
    editName->setText(fData->name());
    editPrice->setText(QString("%1").arg(fData->price()));
    editExternalCode->setText(fData->externalCode());
    editDescription->setText(fData->description());
    editHydroCarbonat->setText(QString("%1").arg(fData->hydroCarbonat()));
    editFat->setText(QString("%1").arg(fData->fat()));
    editProtein->setText(QString("%1").arg(fData->protein()));
    editCalories->setText(QString("%1").arg(fData->calories()));
    chkOutOfStore->setChecked(fData->outOfStore());
    chkEqExport->setChecked(fData->eqExport());    
    labelPicture->setPixmap(fData->picture());
    editBarcode->setText(fData->barcode());
    editMaxDiscount->setText(QString("%1").arg(fData->maxDiscount()));
}

void GoodsElement::init()
{
    editDescription->setTextFormat( Qt::RichText );    
    QDoubleValidator * validator = new QDoubleValidator(0., 100000., 2, editPrice);
    editPrice->setValidator(validator);
    editHydroCarbonat->setValidator(validator);
    editFat->setValidator(validator);
    editProtein->setValidator(validator);
    editCalories->setValidator(validator);
    editMaxDiscount->setValidator(new QIntValidator(0, 100, editMaxDiscount));
  
    QGridLayout * l = new QGridLayout(toolbarParent, 2, 3);
    setupFileActions();
    setupEditActions();
    setupTextActions();    
    doConnections();
}

void GoodsElement::update()
{
    if(!fData) return;
    fData->setParent(parentGroup);
    fData->setName(editName->text());
    fData->setPrice(editPrice->text().toDouble());
    fData->setExternalCode(editExternalCode->text());
    fData->setDescription(editDescription->text());
    fData->setHydroCarbonat(editHydroCarbonat->text().toDouble());
    fData->setFat(editFat->text().toDouble());
    fData->setProtein(editProtein->text().toDouble());    
    fData->setCalories(editCalories->text().toDouble());    
    fData->setPicture(*labelPicture->pixmap());
    fData->setOutOfStore(chkOutOfStore->isChecked());
    fData->setEqExport(chkEqExport->isChecked());    
    fData->setBarcode(editBarcode->text());
    fData->setMaxDiscount(editMaxDiscount->text().toInt());
}

void GoodsElement::ok()
{
    update();
    accept();
}

void GoodsElement::setupFileActions()
{
    QToolBar *tb = new QToolBar("", NULL, toolbarParent);
    QPopupMenu *menu = new QPopupMenu( editor );

    QAction *a;
    a = new QAction( tr( "Open" ), QPixmap::fromMimeSource("fileopen.png" ), tr( "&Open..." ), CTRL + Key_O, editor, "fileOpen" );
    connect( a, SIGNAL( activated() ), this, SLOT( fileOpen() ) );
    a->addTo( tb );
    a->addTo( menu );
    menu->insertSeparator();
    a = new QAction( tr( "Save" ), QPixmap::fromMimeSource( "filesave.png" ), tr( "&Save..." ), CTRL + Key_S, editor, "fileSave" );
    connect( a, SIGNAL( activated() ), this, SLOT( fileSave() ) );
    a->addTo( tb );
    a->addTo( menu );
    menu->insertSeparator();
    tb->setFixedSize(tb->sizeHint());
    toolbarParent->layout()->add(tb);
}

void GoodsElement::setupEditActions()
{
    QToolBar *tb = new QToolBar("", NULL, toolbarParent);
    QPopupMenu *menu = new QPopupMenu( editor );
    
    QAction *a;
    a = new QAction( tr( "Undo" ), QPixmap::fromMimeSource( "undo.png" ), tr( "&Undo" ), CTRL + Key_Z, editor, "editUndo" );
    connect( a, SIGNAL( activated() ), editDescription, SLOT( undo() ) );
    a->addTo( tb );
    a->addTo( menu );
    a = new QAction( tr( "Redo" ), QPixmap::fromMimeSource( "redo.png" ), tr( "&Redo" ), CTRL + Key_Y, editor, "editRedo" );
    connect( a, SIGNAL( activated() ), editDescription, SLOT( redo() ) );
    a->addTo( tb );
    a->addTo( menu );
    menu->insertSeparator();
    a = new QAction( tr( "Cut" ), QPixmap::fromMimeSource( "editcut.png" ), tr( "&Cut" ), CTRL + Key_X, editor, "editCut" );
    connect( a, SIGNAL( activated() ), editDescription, SLOT( cut() ) );
    a->addTo( tb );
    a->addTo( menu );
    a = new QAction( tr( "Copy" ), QPixmap::fromMimeSource( "editcopy.png" ), tr( "C&opy" ), CTRL + Key_C, this, "editCopy" );
    connect( a, SIGNAL( activated() ), editDescription, SLOT( copy() ) );
    a->addTo( tb );
    a->addTo( menu );
    a = new QAction( tr( "Paste" ), QPixmap::fromMimeSource( "editpaste.png" ), tr( "&Paste" ), CTRL + Key_V, editor, "editPaste" );
    connect( a, SIGNAL( activated() ), editDescription, SLOT( paste() ) );
    a->addTo( tb );
    a->addTo( menu );
    tb->setFixedSize(tb->sizeHint());
    toolbarParent->layout()->add(tb);
}

void GoodsElement::setupTextActions()
{
    QToolBar *tb = new QToolBar("", NULL, toolbarParent);
    QPopupMenu *menu = new QPopupMenu( this );

    QComboBox * comboStyle = new QComboBox( FALSE, tb );
    comboStyle->insertItem( tr("Standard") );
    comboStyle->insertItem( tr("Bullet List (Disc)") );
    comboStyle->insertItem( tr("Bullet List (Circle)") );
    comboStyle->insertItem( tr("Bullet List (Square)") );
    comboStyle->insertItem( tr("Ordered List (Decimal)") );
    comboStyle->insertItem( tr("Ordered List (Alpha lower)") );
    comboStyle->insertItem( tr("Ordered List (Alpha upper)") );
    connect( comboStyle, SIGNAL( activated( int ) ),
	     this, SLOT( textStyle( int ) ) );

    QComboBox * comboFont = new QComboBox(TRUE, tb, "comboFont");
    QFontDatabase db;
    comboFont->insertStringList( db.families() );
    connect( comboFont, SIGNAL( activated( const QString & ) ), editDescription, SLOT( setFamily( const QString & ) ) );
    comboFont->lineEdit()->setText( QApplication::font().family() );

    QComboBox * comboSize = new QComboBox(TRUE, tb, "comboSize");
    QValueList<int> sizes = db.standardSizes();
    QValueList<int>::Iterator it = sizes.begin();
    for ( ; it != sizes.end(); ++it )
	comboSize->insertItem( QString::number( *it ) );
    connect( comboSize, SIGNAL( activated( const QString & ) ), this, SLOT( textSize( const QString & ) ) );
    comboSize->lineEdit()->setText( QString::number( QApplication::font().pointSize() ) );
    ((QGridLayout*)toolbarParent->layout())->addMultiCellWidget (tb, 1, 1, 0, 2);    
    
    tb = new QToolBar("", NULL, toolbarParent);    
    QAction * actionTextBold = new QAction( tr( "Bold" ), QPixmap::fromMimeSource( "textbold.png" ), tr( "&Bold" ), CTRL + Key_B, this, "textBold" );
    connect( actionTextBold, SIGNAL(toggled(bool)), editDescription, SLOT(setBold(bool)));
    actionTextBold->addTo( tb );
    actionTextBold->addTo( menu );
    actionTextBold->setToggleAction( TRUE );
    QAction * actionTextItalic = new QAction( tr( "Italic" ), QPixmap::fromMimeSource( "textitalic.png" ), tr( "&Italic" ), CTRL + Key_I, this, "textItalic" );
    connect(actionTextItalic, SIGNAL( toggled(bool) ), editDescription, SLOT(setItalic(bool)));
    actionTextItalic->addTo( tb );
    actionTextItalic->addTo( menu );
    actionTextItalic->setToggleAction( TRUE );
    QAction * actionTextUnderline = new QAction( tr( "Underline" ), QPixmap::fromMimeSource( "textunderline.png" ), tr( "&Underline" ), CTRL + Key_U, this, "textUnderline" );
    connect( actionTextUnderline, SIGNAL(toggled(bool)), editDescription, SLOT(setUnderline(bool)));
    actionTextUnderline->addTo( tb );
    actionTextUnderline->addTo( menu );
    actionTextUnderline->setToggleAction( TRUE );
    menu->insertSeparator();

    QActionGroup *grp = new QActionGroup( this );
    grp->setExclusive( TRUE );
    connect( grp, SIGNAL( selected( QAction* ) ), this, SLOT( textAlign( QAction* ) ) );
   
    QAction * actionAlignLeft = new QAction( tr( "Left" ), QPixmap::fromMimeSource( "textleft.png" ), tr( "&Left" ), CTRL + Key_L, grp, "textLeft" );    
    actionAlignLeft->addTo( tb );
    actionAlignLeft->addTo( menu );
    actionAlignLeft->setToggleAction( TRUE );
    QAction * actionAlignCenter = new QAction( tr( "Center" ), QPixmap::fromMimeSource( "textcenter.png" ), tr( "C&enter" ), CTRL + Key_M, grp, "textCenter" );
    actionAlignCenter->addTo( tb );
    actionAlignCenter->addTo( menu );
    actionAlignCenter->setToggleAction( TRUE );
    QAction * actionAlignRight = new QAction( tr( "Right" ), QPixmap::fromMimeSource( "textright.png" ), tr( "&Right" ), CTRL + Key_R, grp, "textRight" );
    actionAlignRight->addTo( tb );
    actionAlignRight->addTo( menu );
    actionAlignRight->setToggleAction( TRUE );
    QAction * actionAlignJustify = new QAction( tr( "Justify" ), QPixmap::fromMimeSource( "textjustify.png" ), tr( "&Justify" ), CTRL + Key_J, grp, "textjustify" );
    actionAlignJustify->addTo( tb );
    actionAlignJustify->addTo( menu );
    actionAlignJustify->setToggleAction( TRUE );

    menu->insertSeparator();

    QPixmap pix( 16, 16 );
    pix.fill( black );
    QAction * actionTextColor = new QAction( tr( "Color" ), pix, tr( "&Color..." ), 0, this, "textColor" );
    connect( actionTextColor, SIGNAL( activated() ), this, SLOT( textColor()));
    actionTextColor->addTo( tb );
    actionTextColor->addTo( menu );
        
    ((QGridLayout*)toolbarParent->layout())->addWidget (tb, 0, 2);
    QSpacerItem * spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    ((QGridLayout*)toolbarParent->layout())->addItem (spacer, 0, 3);        
}

void GoodsElement::fileOpen()
{
    QString fn = QFileDialog::getOpenFileName( QString::null, tr( "HTML-Files (*.htm *.html)" ), this );
    QFile f(fn);
    f.open(IO_ReadOnly);
    QTextStream s((QIODevice*)&f);
    s.setEncoding(QTextStream::UnicodeUTF8);
    if ( !fn.isEmpty() )
	editDescription->setText(s.read());
    editDescription->setTextFormat( Qt::RichText );
}


void GoodsElement::fileSave()
{
    QString fn = QFileDialog::getSaveFileName( QString::null, tr( "HTML-Files (*.htm *.html)" ), this );
    if ( !fn.isEmpty() ) 
    {
	QFile file(fn);
	if (!file.open(IO_WriteOnly))
	    return;
	QTextStream ts(&file);
	ts << editDescription->text();	
    }    
}

void GoodsElement::textStyle( int i )
{
    if ( i == 0 ) editDescription->setParagType( QStyleSheetItem::DisplayBlock, QStyleSheetItem::ListDisc );
    else if ( i == 1 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListDisc );
    else if ( i == 2 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListCircle );
    else if ( i == 3 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListSquare );
    else if ( i == 4 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListDecimal );
    else if ( i == 5 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListLowerAlpha );
    else if ( i == 6 ) editDescription->setParagType( QStyleSheetItem::DisplayListItem, QStyleSheetItem::ListUpperAlpha );
    editDescription->viewport()->setFocus();
}

void GoodsElement::textSize( const QString &p )
{
    editDescription->setPointSize( p.toInt() );
    editDescription->viewport()->setFocus();
}

void GoodsElement::textAlign( QAction *a )
{
    qDebug(a->name());
    if ( a->name() == "textLeft" ) editDescription->setAlignment( AlignLeft );
    else if ( a->name() == "textCenter" ) editDescription->setAlignment( AlignHCenter );
    else if ( a->name() == "textRight" ) editDescription->setAlignment( AlignRight );
    else if ( a->name() == "textJustify" ) editDescription->setAlignment( AlignJustify );
}

void GoodsElement::textColor()
{
    QColor col = QColorDialog::getColor( editDescription->color(), this );
    if ( !col.isValid() )
	return;
    editDescription->setColor( col );
    QPixmap pix( 16, 16 );
    pix.fill( col );
    ((QAction*)sender())->setIconSet( pix );
}

void GoodsElement::doConnections()
{
    connect( editDescription, SIGNAL( currentFontChanged( const QFont & ) ),
	     this, SLOT( fontChanged( const QFont & ) ) );
    connect( editDescription, SIGNAL( currentColorChanged( const QColor & ) ),
	     this, SLOT( colorChanged( const QColor & ) ) );
    connect( editDescription, SIGNAL( currentAlignmentChanged( int ) ),
	     this, SLOT( alignmentChanged( int ) ) );
}

void GoodsElement::fontChanged( const QFont &f )
{
    ((QComboBox*)toolbarParent->child("comboFont"))->lineEdit()->setText( f.family() );
    ((QComboBox*)toolbarParent->child("comboSize"))->lineEdit()->setText( QString::number( f.pointSize() ) );
    ((QAction*)child("textBold"))->setOn( f.bold() );
    ((QAction*)child("textItalic"))->setOn( f.italic() );
    ((QAction*)child("textUnderline"))->setOn( f.underline() );
}

void GoodsElement::colorChanged( const QColor &c )
{
    QPixmap pix( 16, 16 );
    pix.fill( c );
    ((QAction*)child("textColor"))->setIconSet( pix );
}

void GoodsElement::alignmentChanged( int a )
{
    if ( ( a == AlignAuto ) || ( a & AlignLeft )) ((QAction*)child("textLeft"))->setOn( TRUE );    else if ( ( a & AlignHCenter)) ((QAction*)child("textCenter"))->setOn( TRUE );
    else if ( ( a & AlignRight)) ((QAction*)child("textRight"))->setOn( TRUE );
    else if ( ( a & AlignJustify)) ((QAction*)child("textJustify"))->setOn( TRUE );
}
