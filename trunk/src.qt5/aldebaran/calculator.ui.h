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

void alCalculator::add(QString num)
{
    QString val = QString("%1").arg(cop);
    if(point && val.find('.')<0) val += ".";
    val+=num;
    cop = val.toDouble();
    lcdNumber->display(cop);
}

void alCalculator::on0()
{
    add("0");
}


void alCalculator::on1()
{
    add("1");
}

void alCalculator::on2()
{
    add("2");
}

void alCalculator::on3()
{
    add("3");
}

void alCalculator::on4()
{
    add("4");
}

void alCalculator::on5()
{
    add("5");
}

void alCalculator::on6()
{
    add("6");
}

void alCalculator::on7()
{
    add("7");
}

void alCalculator::on8()
{
    add("8");
}

void alCalculator::on9()
{
    add("9");
}

void alCalculator::onEq()
{
    if(cop==0.) cop = sop;
    switch(op)
    {
    case '+' : res+=cop; break;
    case '-' : res-=cop; break;
    case '*' : res*=cop; break;
    case '/' : res/=cop; break;
    default: sop = cop; res = cop; cop = 0.; return;
    }
    lcdNumber->display(res);
    sop = cop;
    cop = 0.;
    point = FALSE;
}

void alCalculator::onPlus()
{
    if(op!='+') sop = 0.;    
    onEq();
    op = '+';    
}

void alCalculator::onMinus()
{
    if(op!='-') sop = 0.;
    onEq();
    op = '-';    
}

void alCalculator::onMul()
{
    onEq();
    op = '*';    
}

void alCalculator::onDiv()
{
    onEq();
    op = '/';    
}

void alCalculator::onPlusMinus()
{
    cop=-cop;
    lcdNumber->display(cop);
}

void alCalculator::onBackspace()
{
    QString val = QString("%1").arg(cop);
    val = val.left(val.length()-1);
    cop = val.toDouble();
    lcdNumber->display(cop);
}


void alCalculator::onC()
{
    cop=0;
    lcdNumber->display(cop);
}

void alCalculator::onCE()
{
    res = 0.;
    cop = 0.;
    op = 0;
    lcdNumber->display(cop);
}

void alCalculator::on_()
{
    add(".");
    point = TRUE;    
}

double alCalculator::value()
{
    return lcdNumber->value();
}

void alCalculator::setValue( double initVal )
{
    cop = initVal;
    res = initVal;
    if(initVal==(int)initVal) cop = (int)initVal;
    lcdNumber->display(cop);
}

void alCalculator::init()
{
    point = FALSE;
    cop = 0;
    res = 0;
}
