/**
 * Complex World - Research & Educational Project
 * Copyright (C) T.Sang Tran aka "Nerdox" <t.sang.tran@outlook.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __Application_h__
#define __Application_h__


// ************************************************************
// Based on this wiki:
// http://www.qtcentre.org/wiki/index.php?title=Dynamic_translation_in_Qt4_applications
// ************************************************************


// Qt includes
#include <QApplication>
#include <QHash>
#include <QStringList>


// ************************************************************
// Class Forward Declarations
// ************************************************************
class QAction;
class QDir;
class QTranslator;



namespace ndx {

 
// ************************************************************
// Class Forward Declarations
// ************************************************************
class MainWindow;




/**
 * Main Qt application.
 */
class Application : public QApplication {
    Q_OBJECT

public:
	// ************************************************************
	// Type Definition Declarations
	// ************************************************************
	/**
	 * List of translators.
	 */
	typedef QHash<QString, QTranslator*> Translators;
    



	// ************************************************************
	// Member Declarations
	// ************************************************************
    /**
     * Default constructor.
	 * @param argc Number of arguments.
	 * @param argv List of arguments.
     */
	Application(int& argc, char** argv);
    
	
	/**
	 * Default destructor.
	 */
	~Application();


	/**
	 * Shutdown the application.
	 */
    void shutDown();


	/**
	 * Start up the application.
	 * @return True on success.
	 */
    bool startUp();


public slots:
	/**
	 * Close the application.
	 */
    void close();


	/**
	 * Set language.
	 * @param action Action that contains the new language data.
	 */
    void setLanguage(QAction* action);


protected:
	// ************************************************************
	// Structure Declarations
	// ************************************************************
	/**
	 * Path.
	 */
	struct Paths {
		/**
		 * Path to the language directory.
		 */
		QString mLanguage;


		/**
		 * Path to the plug-in directory.
		 */
		QString mPlugin;
	} mPath;




	// ************************************************************
	// Member Declarations
	// ************************************************************
	/**
	 * Load translation based on the path string.
	 * @param path the string path.
	 */
    void loadTranslations(const QString& path);
    
	/**
	 * Load translation based on directory.
	 * @param dir Directory.
	 */
	void loadTranslations(const QDir& dir);


	/**
	 * Setup connections.
	 * @return True on success.
	 */
    bool setupConnections();


	/**
	 * Setup final step.
	 * @param True on success.
	 */
    bool setupFinalSteps();


	/**
	 * Setup GUI.
	 * @param True on success.
	 */
    bool setupGuis();


	/**
	 * Current translator.
	 */
    QTranslator* mCurrentTranslator;


	/**
	 * The main window.
	 */
    MainWindow* mMainWindow;


	/**
	 * List of translations.
	 */
    Translators mTranslators;


}; // End class Application


} // End namespace ndx


#endif // __Application_h__
