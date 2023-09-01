/***************************************************************************//**
 * @file win32_MainWindow.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains a definition of the 'MainWindow' class which inherits from
 * the 'BaseWindow' class. Inherit this 'MainWindow' class for a basic window
 * functionality.
 *
 * @version 1.0.0
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/**
 * @brief Contains a definition of the 'MainWindow' class which inherits from
 * the 'BaseWindow' class. Inherit this 'MainWindow' class for a basic window
 * functionality.
 *
 */
#define _WIN32_MAINWINDOW_HPP_

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
