package testify

import (
	"errors"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSth(t *testing.T) {
	assert.True(t, true, "True is true")
	assert.Equal(t, 123, 123, "should be equal")
	//assert.Nil(t, object)
	var err = errors.New("This is a error")
	assert.Error(t, err)

	assert.Contains(t, err.Error(), "This is a")
}
