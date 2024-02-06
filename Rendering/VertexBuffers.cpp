#include "VertexBuffers.h"

VertexBuffers::VertexBuffers() {
	_layout = new VertexBufferLayout();
}

VertexBuffers::~VertexBuffers() {
	delete _layout;
}

void VertexBuffers::BindLayout() {
	int pointer = 0;
	for (int i = 0; i < _layout->GetLayout().size(); i++) {
		const LayoutElement& layout_elt = _layout->GetLayout()[i];
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, layout_elt.vbo);
		glVertexAttribPointer(i, layout_elt.count, layout_elt.type, GL_FALSE, 0, (const void*)(0));
	}
}