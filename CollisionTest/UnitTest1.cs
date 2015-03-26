using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace CollisionTest
{
    [TestClass]
    public class UnitTest1
    {

        [TestMethod]
        public void detectCollision()
        {
            int x1, x2, y1, y2;
            int width, height;
            x1 = 0;
            x2 = 32;
            y1 = 0;
            y2 = 0;
            width = 32;
            height = 32;

            int result = Math.Abs(x1-x2) + Math.Abs(y1-y2);
            bool detectCollision = false;

            if (result < (width + height))
            {
                detectCollision = true;
            }

            Assert.IsTrue(detectCollision);
        }
    }
}
