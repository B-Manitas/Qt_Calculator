#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Arguments declarations.
    m_operator = new QString;
    m_nbMax = new int(99999999);

    // Numbers x and y as QString.
    m_xStr = new QString;
    m_yStr = new QString;

    // Math error string.
    m_nan = new QString("Math Error");

    // Numbers x and y as double.
    m_xValue = new double(0);
    m_yValue = new double(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Make a basic mathematical operations.
 * @param operatorValue (QString) The symbol of the mathematical operation.
 * @param x (double) The first number.
 * @param y (double) The second number.
 * @return (double) The result of the operation mathematic.
 */
double MainWindow::computeOperation(QString const& operatorValue,
                                    double const& x, double const& y)
{
    if(operatorValue=="+"){
        return x+y;
    }

    else if(operatorValue=="-"){
        return x - y;
    }

    else if(operatorValue=="*"){
        return x * y;
    }

    else if(operatorValue=="/"){
        if(y!=0){
            return x / y;
        }
    }

    return NAN;
}

/**
 * @brief Reset all arguments and enable all buttons.
 */
void MainWindow::resetOperation()
{
    // Reset all arguments.
    *m_xStr = "";
    *m_yStr = "";
    *m_operator = "";

    *m_xValue = 0;
    *m_yValue = 0;

    // Make sure all operator buttons are enabled.
    ui->btnOperatorDivide->setEnabled(true);
    ui->btnOperatorMultiply->setEnabled(true);
    ui->btnOperatorPlus->setEnabled(true);
    ui->btnOperatorMinus->setEnabled(true);
    ui->btnOperatorEqual->setEnabled(true);

    // Reset the display of the result screen.
    ui->lblScreenResult->setText("0");
}

/**
 * @brief (Slot Methods) Gets value of the digit buttons pressed by the user.
 */
void MainWindow::digitPressed()
{
    // Get the buttons pressed.
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    // Check if the previous operations was not an error maths,
    // such as 0 divide by 0;
    if(*m_xStr==*m_nan){
       resetOperation();
    }

    // Select which arguments (x or y) attribute the value of the pressed buttons.
    // Make sure the number is less than max number.
    if(m_operator->isEmpty() && *m_xValue<*m_nbMax){
        *m_xStr += button->text();
        *m_xValue = m_xStr->toDouble();
        ui->lblScreenResult->setText(*m_xStr);
    }

    else if(!m_operator->isEmpty() && *m_yValue<*m_nbMax){
        *m_yStr += button->text();
        *m_yValue = m_yStr->toDouble();
        ui->lblScreenResult->setText(*m_yStr);
    }
}

/**
 * @brief (Slot Methods) Gets value of the operator buttons pressed by the user.
 */
void MainWindow::operatorPressed()
{
    // Get the buttons pressed.
    QPushButton *button = qobject_cast<QPushButton*>(sender());

    // If y is not null, then make a new operation based to x and y arguments.
    // Then, set the result of the operation to x and delete the value from y.
    if(!m_yStr->isEmpty()){
        // Computes the operation based on the operator and the x, y arguments.
        *m_xValue = computeOperation(*m_operator, *m_xValue, *m_yValue);

        // Check if x argument return nan value.
        if(isnan(*m_xValue)){
            // Informs to the user of the math error.
            *m_xStr = *m_nan;

            // Disables all operator buttons due to math error.
            ui->btnOperatorDivide->setEnabled(false);
            ui->btnOperatorMultiply->setEnabled(false);
            ui->btnOperatorPlus->setEnabled(false);
            ui->btnOperatorMinus->setEnabled(false);
            ui->btnOperatorEqual->setEnabled(false);
        }

        else{
            // Set the result of the computation to the argument x as string.
            *m_xStr = QString::number(*m_xValue);
        }

        // Reset y argument.
        *m_yStr = "";
        *m_yValue = 0;
    }

    // Prevent the user from selecting an operator before pressing a number.
    if(!m_xStr->isEmpty()){
        *m_operator = button->text();
        ui->lblScreenResult->setText(*m_xStr + *m_operator);
    }
}

void MainWindow::negativeNb()
{
    QString *prtNb(0);

    // Select the pointer to the number argument.
    if(m_yStr->isEmpty()){
       prtNb = m_xStr;
    }else{
        prtNb = m_yStr;
    }

    // Remove the first character if it's a minus.
    if(*prtNb->constBegin()=="-"){
        prtNb->remove(0, 1);
    }

    // Insert a minus at the first position.
    else{
        prtNb->insert(0, QString("-"));
    }

    // Update the display of the result screen.
    ui->lblScreenResult->setText(*prtNb);

    // Assign the opposite value
    if(prtNb==m_xStr){
        *m_xValue = -*m_xValue;
    }else{
        *m_yValue = -*m_yValue;
    }

}
