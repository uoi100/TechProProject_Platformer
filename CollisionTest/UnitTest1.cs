using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace CollisionTest
{
    [TestClass]
    public class UnitTest1
    {
        struct sprite
        {
            public int x;
            public int x2;
            public int y;
            public int y2;
        };

        /// <summary>
        /// Description: Check if (x,y) is inside this sprite
        /// </summary>
        /// <param name="a"></param>
        /// <param name="x"></param>
        /// <param name="y"></param>
        /// <returns></returns>
        bool pointInsideSprite(sprite a, int x, int y)
        {
            int x1 = a.x;
            int x2 = a.x2;
            int y1 = a.y;
            int y2 = a.y2;

            return (x1 < x && x < x2) && (y1 < y && y < y2);
        }

        [TestMethod]
        public void moveRight()
        {
            // (0, 0) Width = 32, Height = 32
            sprite a;
            sprite b;

            a.x = 0;
            a.x2 = 32;
            a.y = 0;
            a.y2 = 32;

            // (32, 0) Width = 32, Height = 32
            b.x = 32;
            b.x2 = 64;
            b.y = 0;
            b.y2 = 32;

            // A is moving to the right by (5, 0)
            int movementX  = a.x2 + 5;
            int movementY = a.y2 / 2;

            // Should Collide
            bool detectCollision = pointInsideSprite(b, movementX, movementY);

            Assert.IsTrue(detectCollision);
        }

        [TestMethod]
        public void moveLeft()
        {
            // (0, 0) Width = 32, Height = 32
            sprite a;
            sprite b;

            a.x = 0;
            a.x2 = 32;
            a.y = 0;
            a.y2 = 32;

            // (32, 0) Width = 32, Height = 32
            b.x = 32;
            b.x2 = 64;
            b.y = 0;
            b.y2 = 32;

            // B is moving to the left by (-5, 0)
            int movementX = b.x - 5;
            int movementY = b.y2 / 2;

            // Should Collide
            bool detectCollision = pointInsideSprite(a, movementX, movementY);

            Assert.IsTrue(detectCollision);
        }
    }
}
