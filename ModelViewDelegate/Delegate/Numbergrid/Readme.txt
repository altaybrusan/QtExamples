This example shows:

> Datatype-specific editor

// SpinBox is registered for all int and double data types
void MainWindow::createModelAndView()
{
    QItemEditorFactory *editorFactory = new QItemEditorFactory;
    QItemEditorCreatorBase *numberEditorCreator = new
            QStandardItemEditorCreator<SpinBox>();
    editorFactory->registerEditor(QVariant::Double,
                                  numberEditorCreator);
    editorFactory->registerEditor(QVariant::Int,
                                  numberEditorCreator);
    QItemEditorFactory::setDefaultFactory(editorFactory);

    view = new QTableView;
    editTriggers = view->editTriggers();
    model = new QStandardItemModel;
    view->setModel(model);
}


inorder to make the item model to be sensitive to double type, look at StandardItem.
each item is of type double under EditRole. This Role and data-type is saved by base class QStandardItem.


    explicit StandardItem(const double value) : QStandardItem()
        { setData(value, Qt::EditRole); }

    QStandardItem *clone() const
        { return new StandardItem(data(Qt::EditRole).toDouble()); }

    QVariant data(int role=Qt::UserRole+1) const
    {
        if (role == Qt::DisplayRole)
            return QString("%1").arg(QStandardItem::data(Qt::EditRole)
                                     .toDouble(), 0, 'f', 3);
        if (role == Qt::TextAlignmentRole)
            return static_cast<int>(Qt::AlignVCenter|Qt::AlignRight);
        return QStandardItem::data(role);
    }
