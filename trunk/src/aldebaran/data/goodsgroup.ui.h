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
void GoodsGroup::selectPicture()
{
    QFileDialog fileDlg(QDir::currentDirPath(), "Images (*.png *.jpg *.bmp)");
    fileDlg.setCaption(tr("Open goods group picture"));
    if(fileDlg.exec()==QDialog::Accepted)
	labelPicture->setPixmap(QPixmap::fromMimeSource(fileDlg.selectedFile()));
}

void GoodsGroup::clearPicture()
{
    labelPicture->setPixmap(QPixmap());
}

void GoodsGroup::setData(alGoodsRecord * data)
{
    fData = data;
    refresh();
}

void GoodsGroup::refresh()
{
    if(!fData) return;
    parentGroup = fData->parent();
    editName->setText(fData->name());
    labelPicture->setPixmap(fData->picture());
    chkEqExport->setChecked(fData->eqExport());    
}

void GoodsGroup::update()
{
    if(!fData) return;
    fData->setParent(parentGroup);
    fData->setName(editName->text());
    fData->setPicture(*labelPicture->pixmap());
    fData->setEqExport(chkEqExport->isChecked());    
}

void GoodsGroup::ok()
{
    update();
    accept();
}
