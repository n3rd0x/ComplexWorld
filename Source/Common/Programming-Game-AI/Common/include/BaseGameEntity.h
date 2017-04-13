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


/**
 * Based on "Programming Game AI by Example".
 * @author Mat Buckland 2002 (fup@ai-junkie.com)
 */


#ifndef _BaseGameEntity_h_
#define _BaseGameEntity_h_


// Local includes

// GLM includes
#include <GLM/glm.hpp>


namespace ndx {


/**
 * Base class to define a common interface for all game entities.
 */
class BaseGameEntity {
public:
    // ************************************************************
    // Enumerator Declarations
    // ************************************************************
    enum EntityType {
        DEFAULT_ENTITY_TYPE = -1
    };




    // ************************************************************
    // Member Declarations
    // ************************************************************
    /**
     * Default destructor.
     */
    virtual ~BaseGameEntity();


    /**
     * Render.
     */
    virtual void render();


    /**
     * Update.
     * @param dt Time since last frame.
     */
    virtual void update(const double dt);



protected:
    /**
     * Default constructor.
     */
    BaseGameEntity();


    /**
     * Constructor with entity type initialisation.
     * @param entType Entity type.
     */
    BaseGameEntity(const int entType);


    /**
     * Constructor with initialisation.
     * @param entType Entity type.
     * @param pos Position.
     * @param r Bounding radius.
     */
    BaseGameEntity(const int entType, const glm::vec2& pos, const double r);


    /**
     * Constructor with entity type and force ID initialisation.
     * @param entType Entity type.
     * @param forceID ID to set.
     * @remarks Using force ID can be used when a previously created entity has
     *          been removed and deleted from the game for some reason.
     *          USE WITH CAUTION!
     */
    BaseGameEntity(const int entType, const int forceID);


    /**
     * Length of the bounding radius.
     */
    double mBoundingRadius;


    /**
     * Position.
     */
    glm::vec2 mPosition;


    /**
     * Scale.
     */
    glm::vec2 mScale;




private:
    /**
     * @return Next valid ID.
     */
    int nextValidID();


    /**
     * Entity type.
     */
    int mEntityType;


    /**
     * Unique ID for each entity.
     */
    int mId;


    /**
     * A generic flag.
     */
    bool mTag;




    // ************************************************************
    // Static Member Declarations
    // ************************************************************
    /**
     * Next valid ID.
     */
    static int mNextId;




};  // End class BaseGameEntity


}  // End namespace ndx


#endif  // _BaseGameEntity_h_
