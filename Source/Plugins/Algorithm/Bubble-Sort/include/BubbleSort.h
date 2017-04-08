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


#ifndef __BubbleSort_h__
#define __BubbleSort_h__


// Local includes
#include "Plugin.h"
#include <ui_BubbleSort.h>


namespace ndx {


// ************************************************************
// Class Forward Declarations
// ************************************************************
class RandomNumber;



 
/**
 * Echo form sample.
 */
class BubbleSort : public Plugin, public Ui::BubbleSort {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "ndx.Algorithms.BubbleSort" FILE "BubbleSort.json")
	Q_INTERFACES(ndx::Plugin);

public:
	// ************************************************************
	// Member Declarations
	// ************************************************************
    /**
     * Default constructor.
     */
	BubbleSort();
    
	
	/**
	 * Default destructor.
	 */
	~BubbleSort();


	/**
	 * Shutdown the plug-in.
	 */
    void shutDown();


	/**
	 * Start up the plug-in.
	 * @return True on success.
	 */
    bool startUp(QWidget* parent);


protected:
    // ************************************************************
    // Enumerator Declarations
    // ************************************************************
    /**
     * Highlight states.
     */
    enum Highlights {
        /**
         * Highlight when compare items.
         */
        HL_COMPARE,


        /**
         * Continue comparing.
         */
        HL_COMPARE_CONTINUE,


        /**
         * Highlight when we want to delay during compare.
         */
        HL_COMPARE_DELAY,


        /**
         * Highlight when switch item.
         */
        HL_SWITCH,


        /**
         * Continue switching.
         */
        HL_SWITCH_CONTINUE,


        /**
         * Highlight when we want to delay after switch.
         */
        HL_SWITCH_POST,


        /**
         * Highlight when we want to delay before switch.
         */
        HL_SWITCH_PRE,


        /**
         * Default.
         */
        HL_DEFAULT
    };




    // ************************************************************
    // Structure Declarations
    // ************************************************************
    /**
     * Iterator for looping the data set.
     */
    struct Itearator {
        /**
         * End i.
         */
        int ei;


        /**
         * End j.
         */
        int ej;


        /**
         * Current i index.
         */
        int i;


        /**
         * Current j index.
         */
        int j;


        /**
         * Start i.
         */
        int si;


        /**
         * Start j.
         */
        int sj;


        /**
         * Flag for finished.
         */
        bool finished;


        /**
         * Highlight state.
         */
        Highlights state;


        /**
         * Flag for started.
         */
        bool started;
    } mIterator;




    // ************************************************************
    // Type Definition Declarations
    // ************************************************************
    /**
     * List of data set in the grid.
     */
    typedef QList<QLabel*> ViewDataSet;




    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Clear data set.
     */
    void clearDataSet();


    /**
     * Get row and column based on index.
     * @note We could also just use QGridLayout::itemAt(int index)
     * @param [in] idx Index of the data set.
     * @param [out] row The row.
     * @param [out] col The column.
     */
    void getDataSetIndex(const int idx, int& row, int& col);


    /**
     * @param idx Index of the item.
     * @return Item based on the index.
     */
    QLabel* getItem(const int idx);


    /**
     * Get value based on the index.
     * @param idx Index of the item.
     * @return Value of the data set in the grid.
     */
    int getValue(const int idx);


    /**
     * Get value based on the widget.
     * @param widget Label to retrieve value from.
     * @return Value of the widget.
     */
    int getValue(QLabel* widget);


    /**
     * Set index for next iteration.
     * @param [in][out] row The row.
     * @param [in][out] col The column.
     */
    void nextInteration(int& row, int& col);


    /**
     * Switch data index.
     * @param idxA Index a.
     * @param idxB Index b.
     */
    void switchData(const int idxA, const int idxB);


    /**
     * Switch data.
     * @param itemA Item a.
     * @param idxA Index a.
     * @param itemB Item b.
     * @param idxB Index b.
     */
    void switchData(QLabel* itemA, const int idxA, QLabel* itemB, const int idxB);


    /**
     * Visualize based on the highlight state.
     * @param iA Item a.
     * @param iB Item b.
     * @param state The highlight state.
     */
    void visualize(QLabel* iA, QLabel* iB, const Highlights state);


    /**
     * Random number generator.
     */
    RandomNumber* mNumGenerator;


    /**
     * Row span.
     */
    double mRowSpan;


    /**
     * List of view data set.
     */
    ViewDataSet mViewDataSet;


    /**
     * Grid layout for viewing the data set.
     */
    QGridLayout* mViewGridLayout;


protected slots:
    /**
     * Generate data.
     */
    void generateData();


    /**
     * Sort.
     */
    void sort();


}; // End class BubbleSort


} // End namespace ndx


#endif // __BubbleSort_h__
