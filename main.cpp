#include <QCoreApplication>
#include <QDebug>
#include <algorithm>
#include <vector>
#include <string>

QString topOfString(const QString &str, QString &rest, bool &isLetters) {
    QString top;
    if (str.isEmpty()) {
        isLetters = false;
        return top;
    }
    bool startsWithLetter = !str[0].isDigit();
    if (startsWithLetter)
        for(QChar c : str) {
            if (!c.isDigit()) {
                isLetters = true;
                top.append(c);
            } else {
                rest = str.mid(top.length(), str.length());
                break;
            }
        }
    else
        for(QChar c : str) {
            if (c.isDigit() || c == '.' || c == '-') {
                top.append(c);
            } else {
                rest = str.mid(top.length(), str.length());
                break;
            }
        }

    return top;
}

bool compareStringsRecursively(const QString &l, const QString &r) {
    qDebug() << "[ compareStringsRecursively ] " << l << ", " << r;
    // TODO: check if both strings have length OR startWithletters must return bool isEnd
    bool is_lTopLetters, is_rTopLetters = false;
    QString lRest, rRest;
    QString lTop = topOfString(l, lRest, is_lTopLetters);
    QString rTop = topOfString(r, rRest, is_rTopLetters);
    qDebug() << lTop << lRest << is_lTopLetters;
    qDebug() << rTop << rRest << is_rTopLetters;

//    if ((lRest.length() == 0 && rRest.length() != 0))
//        return true;
//    if (lRest.length() != 0 && rRest.length() == 0)
//        return false;

    if (is_lTopLetters && is_rTopLetters) { // BOTH LETTERS
        if (lTop == rTop) {
//            qDebug() << lRest << " | " << rRest;
            return compareStringsRecursively(lRest, rRest);
        } else
            return lTop < rTop;
    } else if (!is_lTopLetters && !is_rTopLetters) { // BOTH DIGITS
        if (lTop == rTop)
            return compareStringsRecursively(lRest, rRest);
        else
            return lTop.toInt() < rTop.toInt();
    } else {
        //            return (!is_lTopLetters);
        if (!is_lTopLetters)
            return true;
        else
            return false;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList v { "1", "1028", "1029", "103", "1030", "10a", "1031" , "2a", "1a", "a1", "a10", "a5",
                    "3aa3", "3aa2", "3aa" };
    // has to become: "1", "1a", "2a", "3aa", "3aa2", "3aa3", "10a", "103",
    // "1028", "1029", "1030", "1031", "a1", "a5", "a10"

    qDebug() << "[ main ]";

    auto numericCompare = [](const QString &l, const QString &r) {
        return compareStringsRecursively(l, r);
    };

    std::sort(v.begin(), v.end(), numericCompare);
    qDebug() << v;

    return a.exec();
}

//    std::string lstr = l.toStdString();
//    std::string rstr = r.toStdString();

//    int li = std::stoi(l);
//    int ri = std::stoi(r);
//    if (li && ri)
//      return li < ri;
//    return l < r;

//    for (auto &i : v)
//    qDebug() << i.c_str();
