#pragma once
#include "cinder/gl/gl.h"
#include "shooting_star.h"

namespace starfall {
class Canvas: public Graphic {
  public:
    Canvas(const glm::vec2 &top_left_corner, double canvas_size, double margin);

    void Draw() const;

    void Update();

    /**
     * Adds vec2 point to boundary points list; star disappears
     * when it touches any of these points
     *
     * @param boundary_point vec2 point to add to list
     */
    void AddPointToBoundaries(const glm::vec2 &boundary_point);

    /**
     * Adds a star to the star list.
     *
     * @param star to add to list
     */
    void AddStarToList(const ShootingStar& star);

    /**
     * Checks if star has disappeared or is in the process of disappearing.
     *
     * @param star to check boundaries for
     * @return true if star is at boundary or in the process of disappearing;
     * false if star has disappeared or has not started disappearing.
     */
    bool IsStarDisappearing(const ShootingStar& star) const;

    const std::vector<ShootingStar>& GetStarList();

  private:
    std::vector<ShootingStar> star_list_;

    // Contains list of positions that creates the mountain boundary
    std::vector<glm::vec2> boundary_points_;

    static bool HasStarDisappeared(const ShootingStar &star);
};
}
