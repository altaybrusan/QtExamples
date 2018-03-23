#include "aqp.h"
#include "scriptform.h"
#include <QDialogButtonBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QScriptEngine>
#if QT_VERSION >= 0x040500
#include <QScriptSyntaxCheckResult>
#endif
#include <QScriptValue>
#include <QVBoxLayout>


ScriptForm::ScriptForm(const QString &script, QWidget *parent)
    : QDialog(parent), m_script(script)
{
    createWidgets();
    createLayout();
    createConnections();

    setWindowTitle(tr("%1 - Script")
                      .arg(QApplication::applicationName()));
}


void ScriptForm::createWidgets()
{
    label = new QLabel(tr("The script will be called once for "
                "every cell in the grid. The cell's value is "
                "in variable <tt>cellValue</tt>, and the cell's "
                "row and column are in variables <tt>cellRow</tt> "
                "and <tt>cellColumn</tt>. The cell's value will "
                "be set to the script's result."));
    label->setWordWrap(true);
    textEdit = new QPlainTextEdit;
    textEdit->setPlainText(!m_script.isEmpty() ? m_script :
            "var result = cellValue;\n"
            "if (result <= 0)\n"
            "    result = cellRow * cellColumn;\n"
            "result;");
    applyToAllRadioButton = new QRadioButton(tr("Apply to &All"));
    applyToAllRadioButton->setChecked(true);
    applyToSelectionRadioButton = new QRadioButton(
            tr("Apply to &Selected"));
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|
                                     QDialogButtonBox::Cancel);
}


void ScriptForm::createLayout()
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(textEdit, 1);
    QHBoxLayout *middleLayout = new QHBoxLayout;
    middleLayout->addWidget(applyToAllRadioButton);
    middleLayout->addWidget(applyToSelectionRadioButton);
    middleLayout->addStretch();
    layout->addLayout(middleLayout);
    layout->addWidget(buttonBox);
    setLayout(layout);
}


void ScriptForm::createConnections()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


void ScriptForm::accept()
{
    m_script = textEdit->toPlainText();
    QScriptEngine javaScriptParser;
    int errorLineNumber = 0;
    QString errorMessage;
#if QT_VERSION >= 0x040500
    QScriptSyntaxCheckResult syntaxResult =
            javaScriptParser.checkSyntax(m_script);
    if (syntaxResult.state() != QScriptSyntaxCheckResult::Valid) {
        errorLineNumber = syntaxResult.errorLineNumber();
        errorMessage = syntaxResult.errorMessage();
        if (errorMessage.isEmpty())
            errorMessage = tr("Syntax Error");
    }
#else
    QScriptValue value(&javaScriptParser, 0);
    javaScriptParser.globalObject().setProperty("cellRow", value);
    javaScriptParser.globalObject().setProperty("cellColumn", value);
    javaScriptParser.globalObject().setProperty("cellValue", value);
    QScriptValue result = javaScriptParser.evaluate(m_script);
    if (javaScriptParser.hasUncaughtException()) {
        errorLineNumber = javaScriptParser
                .uncaughtExceptionLineNumber();
        errorMessage = javaScriptParser.uncaughtException()
                .toString();
    }
#endif
    if (!errorMessage.isEmpty()) {
        AQP::warning(this, tr("Error"),
                tr("Invalid script on line %1:\n%2")
                   .arg(errorLineNumber).arg(errorMessage));
        QTextCursor cursor = textEdit->textCursor();
        cursor.clearSelection();
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down,
                QTextCursor::MoveAnchor, errorLineNumber - 1);
        cursor.select(QTextCursor::LineUnderCursor);
        textEdit->setTextCursor(cursor);
    }
    else
        QDialog::accept();
}
