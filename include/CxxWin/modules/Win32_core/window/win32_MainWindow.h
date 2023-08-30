/**
 * @file Cxxwin/MainWindow.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */
#define WIN32_MAINWINDOW_H

/**
 * @brief The 'MainWindow' class.
 *
 */
class MainWindow : public BaseWindow<MainWindow>
{
public:
    /**
     * @brief
     *
     * @return PCWSTR
     */
    PCWSTR ClassName() const;
    /**
     * @brief
     *
     * @param uMsg
     * @param wParam
     * @param lParam
     * @return LRESULT
     */
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
